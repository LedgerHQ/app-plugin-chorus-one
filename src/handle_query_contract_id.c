#include "plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(ethQueryContractID_t *msg) {
    const context_t *context = (const context_t *) msg->pluginContext;
    // msg->name will be the upper sentence displayed on the screen.
    // msg->version will be the lower sentence displayed on the screen.
    msg->result = ETH_PLUGIN_RESULT_OK;

    switch (context->selectorIndex) {
        case STAKEWISE_DEPOSIT:
            strlcpy(msg->name, "Stakewise", msg->nameLength);
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;

        case STAKEWISE_BURN_OS_TOKEN:
            strlcpy(msg->name, "Stakewise", msg->nameLength);
            strlcpy(msg->version, "Burn OS Token", msg->versionLength);
            break;

        case STAKEWISE_ENTER_EXIT_QUEUE:
            strlcpy(msg->name, "Stakewise", msg->nameLength);
            strlcpy(msg->version, "Enter exit queue", msg->versionLength);
            break;

        case STAKEWISE_CLAIM_EXITED_ASSETS:
            strlcpy(msg->name, "Stakewise", msg->nameLength);
            strlcpy(msg->version, "Claim exited assets", msg->versionLength);
            break;

        case STAKEWISE_LIQUIDATE_OS_TOKEN:
            strlcpy(msg->name, "Stakewise", msg->nameLength);
            strlcpy(msg->version, "Liquidate OS Token", msg->versionLength);
            break;

        case STAKEWISE_MINT_OS_TOKEN:
            strlcpy(msg->name, "Stakewise", msg->nameLength);
            strlcpy(msg->version, "Mint OS Token", msg->versionLength);
            break;

        case STAKEWISE_REDEEM:
            strlcpy(msg->name, "Stakewise", msg->nameLength);
            strlcpy(msg->version, "Redeem", msg->versionLength);
            break;

        case STAKEWISE_REDEEM_OS_TOKEN:
            strlcpy(msg->name, "Stakewise", msg->nameLength);
            strlcpy(msg->version, "Redeem OS Token", msg->versionLength);
            break;

        case EIGENLAYER_DELEGATE_TO:
            strlcpy(msg->name, "Eigenlayer", msg->nameLength);
            strlcpy(msg->version, "Delegate to", msg->versionLength);
            break;

        case EIGENLAYER_INCREASE_DELEGATED_SHARES:
            strlcpy(msg->name, "Eigenlayer", msg->nameLength);
            strlcpy(msg->version, "Increase delegated shares", msg->versionLength);
            break;

        case EIGENLAYER_DECREASE_DELEGATED_SHARES:
            strlcpy(msg->name, "Eigenlayer", msg->nameLength);
            strlcpy(msg->version, "Decrease delegated shares", msg->versionLength);
            break;

        case EIGENLAYER_COMPLETE_QUEUED_WITHDRAWAL:
            strlcpy(msg->name, "Eigenlayer", msg->nameLength);
            strlcpy(msg->version, "Complete queued withdrawal", msg->versionLength);
            break;

        case EIGENLAYER_QUEUE_WITHDRAWAL:
            strlcpy(msg->name, "Eigenlayer", msg->nameLength);
            strlcpy(msg->version, "Queue withdrawal", msg->versionLength);
            break;

        case EIGENLAYER_UNDELEGATE:
            strlcpy(msg->name, "Eigenlayer", msg->nameLength);
            strlcpy(msg->version, "Undelegate", msg->versionLength);
            break;

        case SYMBIOTIC_DEPOSIT:
            strlcpy(msg->name, "Symbiotic", msg->nameLength);
            strlcpy(msg->version, "Deposit", msg->versionLength);
            break;

        case SYMBIOTIC_DEPOSIT_SIG:
            strlcpy(msg->name, "Symbiotic", msg->nameLength);
            strlcpy(msg->version, "Deposit with signature", msg->versionLength);
            break;

        case SYMBIOTIC_ISSUE_DEBT:
            strlcpy(msg->name, "Symbiotic", msg->nameLength);
            strlcpy(msg->version, "Issue debt", msg->versionLength);
            break;

        case SYMBIOTIC_WITHDRAW:
            strlcpy(msg->name, "Symbiotic", msg->nameLength);
            strlcpy(msg->version, "Withdraw", msg->versionLength);
            break;

        default:
            PRINTF("Selector index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}
