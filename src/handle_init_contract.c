#include "plugin_utils.h"
#include "plugin.h"

// Called once to init.
void handle_init_contract(ethPluginInitContract_t *msg) {
    // Make sure we are running a compatible version.
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        // If not the case, return the `UNAVAILABLE` status.
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Double check that the `context_t` struct is not bigger than the maximum size (defined by
    // `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    // Initialize the context (to 0).
    memset(context, 0, sizeof(*context));

    size_t index;
    if (!find_selector(U4BE(msg->selector, 0), SELECTORS, SELECTOR_COUNT, &index)) {
        PRINTF("Error: selector not found!\n");
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }
    context->selectorIndex = index;
    // check for overflow
    if ((size_t) context->selectorIndex != index) {
        PRINTF("Error: overflow detected on selector index!\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    // Set `next_param` to be the first field we expect to parse.
    // EDIT THIS: Adapt the `cases`, and set the `next_param` to be the first parameter you expect
    // to parse.
    switch (context->selectorIndex) {
        case STAKEWISE_DEPOSIT:
        case SYMBIOTIC_DEPOSIT:
        case SYMBIOTIC_DEPOSIT_SIG:
        case SYMBIOTIC_ISSUE_DEBT:
        case SYMBIOTIC_WITHDRAW:
            context->next_param = RECEIVER;
            break;

        case STAKEWISE_BURN_OS_TOKEN:
            context->next_param = OS_TOKEN_SHARES;
            break;

        case STAKEWISE_ENTER_EXIT_QUEUE:
        case STAKEWISE_REDEEM:
            context->next_param = VAULT_SHARES;
            break;

        case STAKEWISE_CLAIM_EXITED_ASSETS:
            context->next_param = POSITION_TICKET;
            break;

        case STAKEWISE_LIQUIDATE_OS_TOKEN:
        case STAKEWISE_REDEEM_OS_TOKEN:
            context->next_param = OS_TOKEN_SHARES;
            break;

        case STAKEWISE_MINT_OS_TOKEN:
            context->next_param = RECEIVER;
            break;

        case EIGENLAYER_DELEGATE_TO:
            context->next_param = OPERATOR;
            break;

        case EIGENLAYER_INCREASE_DELEGATED_SHARES:
        case EIGENLAYER_DECREASE_DELEGATED_SHARES:
            context->next_param = RECEIVER;
            break;

        case EIGENLAYER_COMPLETE_QUEUED_WITHDRAWAL:
            context->next_param = OFFSET_1;
            break;

        case EIGENLAYER_QUEUE_WITHDRAWAL:
            context->next_param = OFFSET_1;
            break;

        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
