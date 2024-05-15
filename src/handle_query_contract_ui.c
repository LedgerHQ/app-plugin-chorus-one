#include "plugin.h"
#include "display_address.h"

static bool deposit_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Deposit", msg->titleLength);
    const uint8_t *eth_amount;
    uint8_t eth_amount_size;

    switch (msg->screenIndex) {
        case 0:
            eth_amount = msg->pluginSharedRO->txContent->value.value;
            eth_amount_size = msg->pluginSharedRO->txContent->value.length;
            // Converts the uint256 number located in `eth_amount` to its string representation and
            // copies this to `msg->msg`.
            return amountToString(eth_amount, eth_amount_size, WEI_TO_ETHER, "ETH", msg->msg, msg->msgLength);
        case 1:
            // If receiver is different from the current address, display the receiver.
            strlcpy(msg->title, "Receiver", msg->titleLength);
            // Get the string representation of the address stored in `context->receiver`. Put it in
            // `msg->msg`.
            displayEthAddress(msg, context->receiver);
            return true;
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
            ret = deposit_ui(msg, context);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
    }
    msg->result = ret ? ETH_PLUGIN_RESULT_OK : ETH_PLUGIN_RESULT_ERROR;
}
