#include "plugin.h"

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

static void handle_stakewise_liquidate_redeem_os_token(ethPluginProvideParameter_t *msg,
                                                       context_t *context) {
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
    switch (context->next_param) {
        case OPERATOR:
            copy_address(context->receiver, msg->parameter, sizeof(context->receiver));
            context->next_param = OFFSET_1;
            break;

        case OFFSET_1:
            context->next_param = APPROVER_SALT;
            break;

        case APPROVER_SALT:
            copy_parameter(context->vault_shares, msg->parameter, sizeof(context->vault_shares));
            context->next_param = OFFSET_2;
            break;

        case OFFSET_2:
            context->next_param = EXPIRY;
            break;

        case EXPIRY:
            copy_parameter(context->timestamp, msg->parameter, sizeof(context->timestamp));
            context->next_param = ARRAY_LEN;
            break;

        case ARRAY_LEN:
            context->next_param = SIGNATURE_1;
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
            semihosted_printf("Param not supported: %d\n", context->next_param);
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
            semihosted_printf("Param not supported: %d\n", context->next_param);
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

        case STAKEWISE_LIQUIDATE_OS_TOKEN:
        case STAKEWISE_REDEEM_OS_TOKEN:
            handle_stakewise_liquidate_redeem_os_token(msg, context);
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

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
