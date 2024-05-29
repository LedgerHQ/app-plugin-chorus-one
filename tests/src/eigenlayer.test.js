import { runTest, eigenlayerContract } from "./utils.js";

runTest(
    "Eigenlayer delegateTo",
    async (eth) => {
        const operator = "0x0102030000000000000000000000000000030201";
        const signatureExpiry = {
            signature:
                "0x0102032222222222222222222222222222222222222222222222222222222222223333333333333333333333333333333333333333333333333333333333040506",
            expiry: "123456789",
        };
        const approverSalt =
            "0xfffefdfffffffffffffffffffffffffffffffffffffffffffffffffffffcfbfa";

        const { data } =
            await eigenlayerContract.populateTransaction.delegateTo(
                operator,

                signatureExpiry,
                approverSalt
            );
        return [data, [7, 0]];
    },
    "0",
    "eigenlayer"
);
