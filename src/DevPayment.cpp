/*
 * Copyright (c) 2018 The resq Core developers
 * Copyright (c) 2019 The Bitcoin Monster Core developers
 * Distributed under the MIT software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 *
 */

#include "DevPayment.h"
//#include "standard.h"
#include "util.h"
#include "chainparams.h"
#include <boost/foreach.hpp>

CAmount DevPayment::getDevPaymentAmount(int blockHeight, CAmount blockReward) {
	 if (blockHeight < 1160){
		 return 0;
	 }
	 return blockReward * 0.01;
}

void DevPayment::FillDevPayment(CMutableTransaction& txNew, int nBlockHeight, CAmount blockReward, CTxOut& txoutDevRet) {
    // make sure it's not filled yet
	txoutDevRet = CTxOut();

    CScript payee;
    // fill payee with the founder address
    payee = GetScriptForDestination(founderAddress.Get());

    // GET FOUNDER PAYMENT VARIABLES SETUP
    CAmount founderPayment = getDevPaymentAmount(nBlockHeight, blockReward);
    // split reward between miner ...
    txNew.vout[0].nValue -= founderPayment;
    // ... and masternode
    txoutDevRet = CTxOut(founderPayment, payee);
    txNew.vout.push_back(txoutDevRet);
    LogPrintf("CMasternodePayments::FillDevPayment -- Dev payment %lld to %s\n", founderPayment, founderAddress.ToString());
}

bool DevPayment::IsBlockPayeeValid(const CTransaction& txNew, const int height, const CAmount blockReward) {
	CScript payee;
	// fill payee with the founder address
	payee = GetScriptForDestination(founderAddress.Get());
	CAmount founderReward = getDevPaymentAmount(height, blockReward);
	BOOST_FOREACH(const CTxOut& out, txNew.vout) {
		if(out.scriptPubKey == payee && out.nValue >= founderReward) {
			return true;
		}
	}

	return false;
}
