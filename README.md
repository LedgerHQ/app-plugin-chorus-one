# Opus plugin for Stakewise vaults and Eigenlayer contracts

This repository contains code for the Opus plugin for stakewise, Eigenlayer and
Symbiotic contracts.

## Smart Contracts and functions

The implemented Smart Contracts and functions can be found in
[PLUGIN_SPECIFICATION.md](./PLUGIN_SPECIFICATION.md)


## Testing

For testing, we use the [Ragger](https://github.com/LedgerHQ/ragger) for
simulating a Ledger device, to run the tests, use the Ledger plugin on VSCode or
run them with:

```bash
pytest ./tests --device <nanos/nanox/nanosp/stax>
```
