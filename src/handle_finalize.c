#include "plugin.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;
    msg->result = ETH_PLUGIN_RESULT_OK;
    msg->uiType = ETH_UI_TYPE_GENERIC;

    switch (context->selectorIndex) {
        case STAKEWISE_DEPOSIT:
        case STAKEWISE_ENTER_EXIT_QUEUE:
        case STAKEWISE_MINT_OS_TOKEN:
        case STAKEWISE_REDEEM:
        case SYMBIOTIC_DEPOSIT:
        case SYMBIOTIC_ISSUE_DEBT:
        case SYMBIOTIC_WITHDRAW:
            msg->numScreens = 1;
            goto add_recipient_screen;

        case STAKEWISE_BURN_OS_TOKEN:
        case EIGENLAYER_UNDELEGATE:
            msg->numScreens = 1;
            break;

        case STAKEWISE_CLAIM_EXITED_ASSETS:
        case EIGENLAYER_QUEUE_WITHDRAWAL:
            msg->numScreens = 3;
            break;

        case STAKEWISE_REDEEM_OS_TOKEN:
        case EIGENLAYER_INCREASE_DELEGATED_SHARES:
        case EIGENLAYER_DECREASE_DELEGATED_SHARES:
            msg->numScreens = 2;
            goto add_recipient_screen;

        case EIGENLAYER_COMPLETE_QUEUED_WITHDRAWAL:
            msg->numScreens = 8;
            break;

        case EIGENLAYER_DELEGATE_TO:
            msg->numScreens = 4;
            break;

        case SYMBIOTIC_DEPOSIT_SIG:
            msg->numScreens = 5;
            goto add_recipient_screen;

        add_recipient_screen:
            if (memcmp(msg->address, context->receiver, ADDRESS_LENGTH) != 0) {
                msg->numScreens += 1;
            }
            break;

        default:
            PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
