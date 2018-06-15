#pragma once

#include <common/net/messages/message.h>

namespace hades {
    class CreditBalanceMessageComposer : public Message {
    public:
        CreditBalanceMessageComposer(int creditBalance) : Message(), creditBalance_(creditBalance) {

        }

        short getId() const override {
            return 1556;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<std::string>(std::to_string(creditBalance_) + ".0");
        }

    private:
        int creditBalance_;
    };

    class CurrenciesBalanceMessageComposer : public Message {
    public:
        CurrenciesBalanceMessageComposer(std::vector<std::tuple<int, int>> balances)
                : Message(), balances_(std::move(balances)) {

        }

        short getId() const override {
            return 3304;
        }

        void compose(Buffer *buffer) const override {
            buffer->write<int>(static_cast<int>(balances_.size()));

            for (auto const &currency : balances_) {
                buffer->write<int>(std::get<0>(currency));
                buffer->write<int>(std::get<1>(currency));
            }
        }

    private:
        std::vector<std::tuple<int, int>> balances_;
    };

}