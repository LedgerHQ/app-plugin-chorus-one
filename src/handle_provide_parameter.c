#include "plugin.h"
#include "utils.h"

static void handle_stakewise_deposit(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case RECEIVER:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = REFERRER;
            break;
        case REFERRER:
            copy_address(context->referrer, msg->parameter, sizeof(context->referrer));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_stakewise_burn_os_token(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case OS_TOKEN_SHARES:
            // Add +16 because the data is in the last 16 bytes of the parameter.
            copy_parameter(context->os_token_shares,
                           msg->parameter + 16,
                           sizeof(context->os_token_shares));
            context->next_param = UNEXPECTED_PARAMETER;
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_stakewise_enter_exit_queue_and_redeem(ethPluginProvideParameter_t *msg,
                                                         context_t *context) {
    switch (context->next_param) {
        case VAULT_SHARES:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = RECEIVER;
            break;

        case RECEIVER:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_stakewise_claim_exited_assets(ethPluginProvideParameter_t *msg,
                                                 context_t *context) {
    switch (context->next_param) {
        case POSITION_TICKET:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = TIMESTAMP;
            break;

        case TIMESTAMP:
            copy_parameter(context->timestamp, msg->parameter, sizeof(context->timestamp));
            context->next_param = EXIT_QUEUE_INDEX;
            break;

        case EXIT_QUEUE_INDEX:
            copy_parameter(context->exit_queue_index,
                           msg->parameter,
                           sizeof(context->exit_queue_index));
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_stakewise_redeem_os_token(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case OS_TOKEN_SHARES:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = OWNER;
            break;

        case OWNER:
            copy_address(context->referrer, msg->parameter, sizeof(context->referrer));
            context->next_param = RECEIVER;
            break;

        case RECEIVER:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_stakewise_mint_os_token(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case RECEIVER:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = OS_TOKEN_SHARES;
            break;

        case OS_TOKEN_SHARES:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = REFERRER;
            break;

        case REFERRER:
            copy_address(context->referrer, msg->parameter, sizeof(context->referrer));
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_eigenlayer_delegate_to(ethPluginProvideParameter_t *msg, context_t *context) {
    uint8_t expected_bytes[3] = {0x60, 0x40, 0x41};
    switch (context->next_param) {
        case OPERATOR:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = OFFSET_1;
            break;

        case OFFSET_1:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[0], 1)) {
                context->next_param = APPROVER_SALT;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case APPROVER_SALT:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = OFFSET_2;
            break;

        case OFFSET_2:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[1], 1)) {
                context->next_param = EXPIRY;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case EXPIRY:
            copy_parameter(context->timestamp, msg->parameter, sizeof(context->timestamp));
            context->next_param = ARRAY_LEN_1;
            break;

        case ARRAY_LEN_1:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[2], 1)) {
                context->next_param = SIGNATURE_1;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case SIGNATURE_1:
            copy_parameter(context->exit_queue_index, msg->parameter, 3);
            context->next_param = SIGNATURE_2;
            break;

        case SIGNATURE_2:
            copy_parameter(context->exit_queue_index + 29, msg->parameter + 30, 2);
            context->next_param = SIGNATURE_3;
            break;

        case SIGNATURE_3:
            copy_parameter(context->exit_queue_index + 31, msg->parameter, 1);
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_eigenlayer_inc_dec_delegated_shares(ethPluginProvideParameter_t *msg,
                                                       context_t *context) {
    switch (context->next_param) {
        case RECEIVER:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = STRATEGY;
            break;

        case STRATEGY:
            copy_address(context->referrer, msg->parameter, sizeof(context->referrer));
            context->next_param = SHARES;
            break;

        case SHARES:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_eigenlayer_complete_queued_withdrawal(ethPluginProvideParameter_t *msg,
                                                         context_t *context) {
    uint8_t expected_bytes[5] = {
        0x80,
        0x01,
        0xe0,
        0x01,
        0x20,
    };
    switch (context->next_param) {
        case OFFSET_1:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[0], 1)) {
                context->next_param = OFFSET_2;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }

            break;

        case OFFSET_2:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[1], 2)) {
                context->next_param = MIDDLEWARE_TIMES_INDEX;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case MIDDLEWARE_TIMES_INDEX:
            copy_parameter(context->exit_queue_index,
                           msg->parameter,
                           sizeof(context->exit_queue_index));
            context->next_param = RECEIVE_AS_TOKENS;
            break;

        case RECEIVE_AS_TOKENS:
            context->bool_var = msg->parameter[31] & 1;
            context->next_param = RECEIVER;
            break;

        case RECEIVER:
            copy_parameter(context->receiver, msg->parameter + 12, 3);
            copy_parameter(context->receiver + 3, msg->parameter + 29, 3);
            context->next_param = DELEGATED_TO;
            break;

        case DELEGATED_TO:
            copy_parameter(context->receiver + 6, msg->parameter + 12, 3);
            copy_parameter(context->receiver + 9, msg->parameter + 29, 3);
            context->next_param = WITHDRAWER;
            break;

        case WITHDRAWER:
            copy_parameter(context->receiver + 12, msg->parameter + 12, 3);
            copy_parameter(context->receiver + 15, msg->parameter + 29, 3);
            context->next_param = NONCE;
            break;

        case NONCE:
            copy_parameter(context->timestamp, msg->parameter, sizeof(context->timestamp));
            context->next_param = START_BLOCK;
            break;

        case START_BLOCK:
            copy_parameter(context->os_token_shares, msg->parameter + 28, 4);
            context->next_param = OFFSET_3;
            break;

        case OFFSET_3:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[2], 1)) {
                context->next_param = OFFSET_4;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case OFFSET_4:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[3], 2)) {
                context->next_param = ARRAY_LEN_1;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case ARRAY_LEN_1:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[1], 1)) {
                context->next_param = STRATEGY;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case STRATEGY:
            copy_parameter(context->referrer, msg->parameter + 12, 3);
            copy_parameter(context->referrer + 3, msg->parameter + 29, 3);
            context->next_param = ARRAY_LEN_2;
            break;

        case ARRAY_LEN_2:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[1], 1)) {
                context->next_param = SHARES;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case SHARES:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = ARRAY_LEN_3;
            break;

        case ARRAY_LEN_3:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[1], 1)) {
                context->next_param = TOKENS;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case TOKENS:
            copy_parameter(context->referrer + 6, msg->parameter + 12, 3);
            copy_parameter(context->referrer + 9, msg->parameter + 29, 3);
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_eigenlayer_queue_withdrawal(ethPluginProvideParameter_t *msg,
                                               context_t *context) {
    uint8_t expected_bytes[5] = {
        0x20,
        0x01,
        0x60,
        0xa0,
    };
    switch (context->next_param) {
        case OFFSET_1:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[0], 1)) {
                context->next_param = ARRAY_LEN_1;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }

            break;

        case ARRAY_LEN_1:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[1], 1)) {
                context->next_param = OFFSET_2;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case OFFSET_2:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[0], 1)) {
                context->next_param = OFFSET_3;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case OFFSET_3:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[2], 1)) {
                context->next_param = OFFSET_4;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case OFFSET_4:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[3], 1)) {
                context->next_param = WITHDRAWER;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case WITHDRAWER:
            context->next_param = ARRAY_LEN_2;
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            break;

        case ARRAY_LEN_2:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[1], 1)) {
                context->next_param = STRATEGY;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case STRATEGY:
            context->next_param = ARRAY_LEN_3;
            copy_address(context->referrer, msg->parameter, sizeof(context->referrer));
            break;

        case ARRAY_LEN_3:
            if (compare_last_n_bytes(msg->parameter, &expected_bytes[1], 1)) {
                context->next_param = SHARES;
            } else {
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                context->next_param = UNEXPECTED_PARAMETER;
            }
            break;

        case SHARES:
            context->next_param = UNEXPECTED_PARAMETER;
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            break;

        // Keep this
        default:
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_eigenlayer_undelegate(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case RECEIVER:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_symbiotic_deposit_issue_debt_withdraw(ethPluginProvideParameter_t *msg,
                                                  context_t *context) {
    switch (context->next_param) {
        case RECEIVER:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = SHARES;
            break;

        case SHARES:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_symbiotic_deposit_sig(ethPluginProvideParameter_t *msg, context_t *context) {
    switch (context->next_param) {
        case RECEIVER:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = SHARES;
            break;

        case SHARES:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = DEADLINE;
            break;

        case DEADLINE:
            copy_parameter(context->timestamp, msg->parameter, sizeof(context->timestamp));
            context->next_param = SIGNATURE_1;
            break;

        case SIGNATURE_1:
            copy_parameter(context->os_token_shares + 15, msg->parameter + 31, 1);
            context->next_param = SIGNATURE_2;
            break;

        case SIGNATURE_2:
            copy_parameter(context->exit_queue_index, msg->parameter, 3);
            copy_parameter(context->exit_queue_index + 3, msg->parameter + 29, 3);
            context->next_param = SIGNATURE_3;
            break;

        case SIGNATURE_3:
            copy_parameter(context->exit_queue_index + 6, msg->parameter, 3);
            copy_parameter(context->exit_queue_index + 9, msg->parameter + 29, 3);
            context->next_param = UNEXPECTED_PARAMETER;
            break;

        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(ethPluginProvideParameter_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    // EDIT THIS: adapt the cases and the names of the functions.
    switch (context->selectorIndex) {
        case STAKEWISE_DEPOSIT:
            handle_stakewise_deposit(msg, context);
            break;

        case STAKEWISE_BURN_OS_TOKEN:
            handle_stakewise_burn_os_token(msg, context);
            break;

        case STAKEWISE_ENTER_EXIT_QUEUE:
        case STAKEWISE_REDEEM:
            handle_stakewise_enter_exit_queue_and_redeem(msg, context);
            break;

        case STAKEWISE_CLAIM_EXITED_ASSETS:
            handle_stakewise_claim_exited_assets(msg, context);
            break;

        case STAKEWISE_REDEEM_OS_TOKEN:
            handle_stakewise_redeem_os_token(msg, context);
            break;

        case STAKEWISE_MINT_OS_TOKEN:
            handle_stakewise_mint_os_token(msg, context);
            break;

        case EIGENLAYER_DELEGATE_TO:
            handle_eigenlayer_delegate_to(msg, context);
            break;

        case EIGENLAYER_INCREASE_DELEGATED_SHARES:
        case EIGENLAYER_DECREASE_DELEGATED_SHARES:
            handle_eigenlayer_inc_dec_delegated_shares(msg, context);
            break;

        case EIGENLAYER_COMPLETE_QUEUED_WITHDRAWAL:
            handle_eigenlayer_complete_queued_withdrawal(msg, context);
            break;

        case EIGENLAYER_QUEUE_WITHDRAWAL:
            handle_eigenlayer_queue_withdrawal(msg, context);
            break;

        case EIGENLAYER_UNDELEGATE:
            handle_eigenlayer_undelegate(msg, context);
            break;

        case SYMBIOTIC_DEPOSIT:
        case SYMBIOTIC_ISSUE_DEBT:
        case SYMBIOTIC_WITHDRAW:
            handle_symbiotic_deposit_issue_debt_withdraw(msg, context);
            break;

        case SYMBIOTIC_DEPOSIT_SIG:
            handle_symbiotic_deposit_sig(msg, context);
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
