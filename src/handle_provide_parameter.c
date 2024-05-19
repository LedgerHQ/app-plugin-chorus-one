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
            copy_parameter(context->os_token_shares, msg->parameter+16, sizeof(context->os_token_shares));
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
            msg->result = ETH_PLUGIN_RESULT_OK;
            handle_stakewise_deposit(msg, context);
            break;

        case STAKEWISE_BURN_OS_TOKEN:
            msg->result = ETH_PLUGIN_RESULT_OK;
            handle_stakewise_burn_os_token(msg, context);
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
