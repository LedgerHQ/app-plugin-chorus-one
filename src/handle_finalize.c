#include "plugin.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    switch(context->selectorIndex) {
        case STAKEWISE_DEPOSIT:
        case STAKEWISE_ENTER_EXIT_QUEUE:
            msg->numScreens = 1;
            msg->result = ETH_PLUGIN_RESULT_OK;
            if (memcmp(msg->address, context->receiver, ADDRESS_LENGTH) != 0) {
                msg->numScreens += 1;
            }
            break;

        case STAKEWISE_BURN_OS_TOKEN:
            msg->numScreens = 1;
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        case STAKEWISE_CLAIM_EXITED_ASSETS:
            msg->numScreens = 3;
            msg->result = ETH_PLUGIN_RESULT_OK;
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
