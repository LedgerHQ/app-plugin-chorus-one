#include "plugin.h"
#include "utils.h"

static bool stakewise_deposit_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Deposit", msg->titleLength);
    const uint8_t *eth_amount;
    uint8_t eth_amount_size;

    switch (msg->screenIndex) {
        case 0:
            eth_amount = msg->pluginSharedRO->txContent->value.value;
            eth_amount_size = msg->pluginSharedRO->txContent->value.length;
            // Converts the uint256 number located in `eth_amount` to its string representation and
            // copies this to `msg->msg`.
            return amountToString(eth_amount,
                                  eth_amount_size,
                                  WEI_TO_ETHER,
                                  "ETH",
                                  msg->msg,
                                  msg->msgLength);
        case 1:
            // If receiver is different from the current address, display the receiver.
            strlcpy(msg->title, "Receiver", msg->titleLength);
            // Get the string representation of the address stored in `context->receiver`. Put it in
            // `msg->msg`.
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_burn_os_token_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "OS shares", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->os_token_shares, 16);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_enter_exit_queue_ui_and_redeem_ui(ethQueryContractUI_t *msg,
                                                        const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Vault shares", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 1:
            // If receiver is different from the current address, display the receiver.
            strlcpy(msg->title, "Receiver", msg->titleLength);
            // Get the string representation of the address stored in `context->receiver`. Put it in
            // `msg->msg`.
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_claim_exited_assets_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Position ticket", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 1:
            strlcpy(msg->title, "Timestamp", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->timestamp, 32);
            return true;

        case 2:
            strlcpy(msg->title, "Exit Queue index", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->exit_queue_index, 32);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_redeem_os_token_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "OsToken shares", msg->titleLength);
            // Use `vault_shares` to store the os_token_shares, in this function
            // OsToken shares are 32 bytes.
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 1:
            strlcpy(msg->title, "Owner", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->referrer, ADDRESS_LENGTH, 3);
            return true;

        case 2:
            strlcpy(msg->title, "Receiver", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool stakewise_mint_os_token_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "OsToken shares", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 1:
            strlcpy(msg->title, "Receiver", msg->titleLength);
            // Use `vault_shares` to store the os_token_shares, in this function
            // OsToken shares are 32 bytes.
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool eigenlayer_delegate_to_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Operator", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;

        case 1:
            strlcpy(msg->title, "Approver Salt", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->vault_shares, 32, 3);
            return true;

        case 2:
            strlcpy(msg->title, "Expiry", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->timestamp, 32);
            return true;

        case 3:
            strlcpy(msg->title, "Signature", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->exit_queue_index, 32, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool eigenlayer_inc_dec_delegated_shares_ui(ethQueryContractUI_t *msg,
                                                   const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Strategy", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->referrer, ADDRESS_LENGTH, 3);
            return true;

        case 1:
            strlcpy(msg->title, "Shares", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 2:
            // If receiver is different from the current address, display the receiver.
            strlcpy(msg->title, "Receiver", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;
    }
    return false;
}

static bool eigenlayer_complete_queued_withdrawal_ui(ethQueryContractUI_t *msg,
                                                     const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Staker", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, 6, 3);
            return true;

        case 1:
            strlcpy(msg->title, "Delegated To", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver + 6, 6, 3);
            return true;

        case 2:
            strlcpy(msg->title, "Withdrawer", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver + 12, 6, 3);
            return true;

        case 3:
            strlcpy(msg->title, "Nonce", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->timestamp, sizeof(context->timestamp));
            return true;

        case 4:
            strlcpy(msg->title, "Start Block", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->uint32_var, sizeof(context->uint32_var));
            return true;

        case 5:
            strlcpy(msg->title, "Strategy", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->referrer, 6, 3);
            return true;

        case 6:
            strlcpy(msg->title, "Shares", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 7:
            strlcpy(msg->title, "Token", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->referrer + 6, 6, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool eigenlayer_queue_withdrawal_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Strategy", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;

        case 1:
            strlcpy(msg->title, "Shares", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 2:
            strlcpy(msg->title, "Withdrawer", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->referrer, ADDRESS_LENGTH, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool eigenlayer_undelegate_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Staker", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool symbiotic_deposit_issue_debt_withdraw_ui(ethQueryContractUI_t *msg,
                                                     const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 1:
            strlcpy(msg->title, "Recipient", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

static bool symbiotic_deposit_sig_ui(ethQueryContractUI_t *msg, const context_t *context) {
    switch (msg->screenIndex) {
        case 0:
            strlcpy(msg->title, "Amount", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->vault_shares, 32);
            return true;

        case 1:
            strlcpy(msg->title, "Deadline", msg->titleLength);
            display_uint_decimal(msg, (uint8_t *) context->timestamp, 32);
            return true;

        case 2:
            strlcpy(msg->title, "V", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->os_token_shares + 15, 0, 1);
            return true;

        case 3:
            strlcpy(msg->title, "R", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->exit_queue_index, 6, 3);
            return true;

        case 4:
            strlcpy(msg->title, "S", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->exit_queue_index + 6, 6, 3);
            return true;

        case 5:
            strlcpy(msg->title, "Recipient", msg->titleLength);
            display_first_and_last_bytes(msg, (uint8_t *) context->receiver, ADDRESS_LENGTH, 3);
            return true;

        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return false;
    }
}

void handle_query_contract_ui(ethQueryContractUI_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    bool ret = false;
    // msg->title is the upper line displayed on the device.
    // msg->msg is the lower line displayed on the device.
    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);

    switch (context->selectorIndex) {
        case STAKEWISE_DEPOSIT:
            ret = stakewise_deposit_ui(msg, context);
            break;

        case STAKEWISE_BURN_OS_TOKEN:
            ret = stakewise_burn_os_token_ui(msg, context);
            break;

        case STAKEWISE_ENTER_EXIT_QUEUE:
        case STAKEWISE_REDEEM:
            ret = stakewise_enter_exit_queue_ui_and_redeem_ui(msg, context);
            break;

        case STAKEWISE_CLAIM_EXITED_ASSETS:
            ret = stakewise_claim_exited_assets_ui(msg, context);
            break;

        case STAKEWISE_REDEEM_OS_TOKEN:
            ret = stakewise_redeem_os_token_ui(msg, context);
            break;

        case STAKEWISE_MINT_OS_TOKEN:
            ret = stakewise_mint_os_token_ui(msg, context);
            break;

        case EIGENLAYER_DELEGATE_TO:
            ret = eigenlayer_delegate_to_ui(msg, context);
            break;

        case EIGENLAYER_INCREASE_DELEGATED_SHARES:
        case EIGENLAYER_DECREASE_DELEGATED_SHARES:
            ret = eigenlayer_inc_dec_delegated_shares_ui(msg, context);
            break;

        case EIGENLAYER_COMPLETE_QUEUED_WITHDRAWAL:
            ret = eigenlayer_complete_queued_withdrawal_ui(msg, context);
            break;

        case EIGENLAYER_QUEUE_WITHDRAWAL:
            ret = eigenlayer_queue_withdrawal_ui(msg, context);
            break;

        case EIGENLAYER_UNDELEGATE:
            ret = eigenlayer_undelegate_ui(msg, context);
            break;

        case SYMBIOTIC_DEPOSIT:
        case SYMBIOTIC_ISSUE_DEBT:
        case SYMBIOTIC_WITHDRAW:
            ret = symbiotic_deposit_issue_debt_withdraw_ui(msg, context);
            break;

        case SYMBIOTIC_DEPOSIT_SIG:
            ret = symbiotic_deposit_sig_ui(msg, context);
            break;

        default:
            PRINTF("Received an invalid selectorIndex\n");
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
