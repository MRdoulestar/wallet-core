// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Transaction.h"
#include "../proto/Cardano.pb.h"
#include "Data.h"

#include <string>
#include <map>

namespace TW::Cardano {

class Signer {
public:
    Proto::SigningInput input;
    TransactionPlan _plan;

    Signer(const Proto::SigningInput& input): input(input) {}

    Proto::SigningOutput sign();
    // Sign using existing plan
    Proto::SigningOutput signWithPlan();
    // Create plan from signing input
    TransactionPlan plan() const;
    // Build encoded transaction
    static Common::Proto::SigningError encodeTransaction(Data& encoded, Data& txId, const Proto::SigningInput& input, const TransactionPlan& plan);
    // Build aux transaction object, using input and plan
    static Common::Proto::SigningError buildTransactionAux(Transaction& tx, const Proto::SigningInput& input, const TransactionPlan& plan);
    static Amount estimateFee(const Proto::SigningInput& input, Amount amount);
    static std::vector<TxInput> selectInputsSimple(const std::vector<TxInput>& inputs, Amount amount);
    // Build list of public keys + signature
    static Common::Proto::SigningError assembleSignatures(std::vector<std::pair<Data, Data>>& signatures, const Proto::SigningInput& input, const TransactionPlan& plan, const Data& txId);
};

} // namespace TW::Cardano