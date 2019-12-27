
<img align="left" width="170" height="40" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/plasmadltlogo.png"> </br>





***
# Investment Fund DAO Protocol
***

## Сontent:
* [Introduction](#introduction)
* [Protocol Applicability](#protocol-applicability)
  *  [Protocol consensus](#protocol-consensus)
  *  [Investor consensus](#investor-consensus)
  *  [Candidate consensus](#candidate-consensus)
* [Protocol Structures](#protocol-structures)
    *  [Token Issue and Configuration](#token-issue-and-configuration)
    *  [Income distribution and automated payouts](#income-distribution-and-automated-payouts)
       * [Sending a deposit to the Investment Fund](#sending-a-deposit-to-the-investment-fund)
       * [Investment Fund Dividend Distribution](#investment-fund-dividend-distribution)
       * [Fund investment allocation](#fund-investment-allocation)
       * [Distribution of income Invest projects](#distribution-of-income-invest-projects)
    *  [Asset Exchange](#income-distribution-and-automated-payouts)
    *  [Voiting systems for project management -  DAO](#voiting-systems-for-project-management-dao)
        * [Delegate Selection](#delegate-selection)
        * [Delegates voting management](#delegates-voting-management)
    *  [External data management system](#external-data-management-system)
        * [Orcale.JS Setup ](#orcale.js-setup )
    *  [Referral Loyalty System](#referral-loyalty-system)
        * [The principle of the referral system](#the-principle-of-the-referral-system)


---------------------------

# Introduction

Investment companies and foundations based on investor confidence through reputation or marketing are trusted, but this does not protect the investor from fund default risks and fraud. Changing the market for open data allows you to approach the subject of investment more carefully, but not the fund. The decision of the consensus fund based on the blockchain PlasmaDLT has the functions of traditional fiat finance in the form of smart digital money with bank processing Swift / Sepa and Visa / Mastercard, programmable smart contracts and tokenized assets with high cryptographic strength, all this allows you to build a completely new and transparent fund with consensual management

Protocol Features:

* Tokenized asset issue and price сonfiguration
* Income distribution and automated payouts
* Asset Exchange
* DAO (Decentralized Autonomous Organizations) Voiting systems for project management
* External data management system
* Referral Loyalty System

Useful links:
* Wallet: https://plasmapay.com
* Explorer: https://plasmadlt.com/monitor
* Git: https://github.com/plasmadlt
* Docker: https://hub.docker.com/r/plasmachain/ion.cdt
* Chain API: https://developer.plasmapay.com/chain.html

**Mainet ChainID**
```
6b40b56f9c93ef51736a3f0a973ff6d64190a68284f164726fa2be8786d49277
```
**Testnet ChainID**
```
f9d5290291c3debff5604a147a1e11505e5d9f9e052d1d9657b61736b7ed4ec2
```
**Gateway Endpoint**

 * ***Mainet***  Liberty P2P adress https://plasmadlt.com/monitor

 * ***Testnet***  Friedman P2P adress https://plasmadlt.com/monitor

---------------------------
# Protocol Applicability


## Protocol consensus
The protocol acts as an immutable business logic scenario in which all members fulfill their immutable role. The protocol ensures the security and authenticity of information. The consensus of the fund is determined by strict voting rules of the participants, where each member has his own role and weight of vote, depending on the transferred or managed capital. Security of the protocol based on the principles of cryptography and data replication in an unchanged form is provided by the PlasmaDLT blockchain nodes.

## Investor consensus

Voting for the selection of candidates and including in trust management by the vote of all investors, the vote being equal to the amount of the investment in the investor’s fund, where the weight of all votes is determined and distributed as a percentage of the total votes of investors.

Perform the functions:

* Voting for candidate selection;
* Voting for the exclusion of a candidate;
* Voting for exceptions to the investment strategy;
* Receiving dividends.

# Candidate Consensus
They perform the function of trusted money management, and are appointed by investors by general vote. The weight of the candidate’s vote is equal to the number of trusted votes from investors, where the weight of all votes is distributed as a percentage of the total number of candidate votes. Role in the management of each candidate serves in decision-making by voting ⅔ the functions of the fund under consideration.


Perform the functions:

* Analytics invest offers;
* Building investment strategies;
* Asset inclusion management;
* Management of asset allocation in investment offers;
* Financial flow management;
* Management in protocol code change.


### Applicable for Organization

* Equity funds;
* Bond funds;
* Mixed investment funds
* Index funds;
* Money market funds;
* Fund funds;
* Real estate funds;
* Funds of especially risky (venture) investments;
* Cryptocurrency funds;
* Private equity funds.


---------------------------

# Protocol Structures

## Token Issue and Configuration

The PlasmaPay platform mechanisms allow the investor to create and distribute custom tokens. Dependns on invest fund business goals,various scenarios could be applied. This document covers the base one, but - we are opened to discuss all the pipelines you are interested in.

Basically, the following are needed for token creation and deployment

 * Deleveloper toolset - ION.CDT, text editor or IDE
 * Smart-contract, written w.r.t ION.CDT tool, based on C++ language
 * Deploy script - bash commands to communicate with Plasma Networks

 Develop toolset - could be easily found within this GitHub repository, please, follow instructions https://github.com/plasmadlt/PlasmaDLT-devtoolkit

 Smart-contract for PlasmaPay network - this is more sophisticated item. This repository contains an example for simple token - please look the following code:

 * ***Token contract*** https://github.com/plasmadlt/plasmadlt-invest-fund/tree/master/src/token

* Basic example Create and Deploy  https://github.com/plasmadlt/Simple-contracts-for-Plasma/tree/master/Create%20simple%20token

 Based on this source code, you could easily create the each token you needed.
 In general, invest-token smart contract should support and implement the following actions:
 ```
  * void create(name issuer, asset maximum_supply);
  * void issue(name to, asset quantity, string memo);
  * void retire(asset quantity, string memo);
  * void transfer(name from, name to, asset quantity, string memo);

  * ... etc, user defined ...
 ```
 Deploy script - bash commands to communicate with Plasma Networks

 Please, find below demo commands. Consider this code as foundation for base pipeline for integrating and deploying.
 PlasmaPay network fully supports this mechanisms.

 #### Create token
```
 docker exec -i <network> sol sol --url --wallet-url  push action ion.token create '{"issuer": «gmsp.admin», "maximum_supply": "10000.0000 GMSP"}' -p ion.token@active
```
 #### Issue token and Send
```
 docker exec -i <network> sol sol --url --wallet-url  push action gmsp issue '{"to":"aaaaaaaaaaaa", "quantity":"10000", "paySysCms": false, "memo": "test issue"}' -p      gmsp.admin@active
```
## Income distribution and automated payouts
### Sending a deposit to the Investment Fund

<img align="сenter" width="440" height="210" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/senddeposit.png"> </br>


The investor sends the investment fund's accounts to the escrow deposit of the investment, in return receives a confirmation of ownership of the fund's share in the form of tokenized obligations of the Investment Fund. The investor can request these obligations back in exchange for investments by the decision of all holders of obligations or exchange them in the secondary market.



### Investment Fund Dividend Distribution

<img align="сenter" width="390" height="190" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/distribution.png"> </br>

Investment fund bank, receives income and distributes it among holders of tokenized fund liabilities



### Fund investment allocation

<img align="сenter" width="390" height="190" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/allocation.png"> </br>

The investment fund distributes investments in investment ideas by voting of delegates' investors, each investment idea forms its own tokenized obligations.



### Distribution of income Invest projects

<img align="сenter" width="370" height="190" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/income.png"> </br>


An investment project receives income and distributes it among holders of tokenized obligations owned by the investment fund.

There are a few major elements, constructing fully connected payout system, related to invest-found.

 * bank account
 * smart-contract, responsible for profit distribution among the holders of tokenized obligations
 * oracle services, kind of smart watchers, execution 24h repeated actions for smart-constracts

 Bank account - this is kinda blockchain account, containing (owning) some funds, which is gonna to be distributed.
 Bank account accepts some funds - as a comission rewards for invest tokens owners, or some compensations for transfers, etc..

 This funds are needed to be distributed - among the token holders.
 Please, pay attention to the following smart-contract, responsible for rewards execution

 * ***Reward contract*** https://github.com/plasmadlt/plasmadlt-invest-fund/tree/master/src/reward

 Based on this API and source code, you can easily implement you own reward system, or you can apply the existing one.
 Take this as a basis, and reward operations would be fully processed.

 One simple command is fairly enough - to deploy this smart contract, after compilation with ION.CDT tool.
 ```
  docker exec -i <network> sol set sol --url --wallet-url  contract gmsp.reward host-share/contracts/accountreward -p accountreward@active*
 ```
 Also, this API call (for example - rewards execution) could be maintained by some serive, oracle watcher. The idea is to execute rewards daily, or onces in some time (12h). Please, refer to the following code sample -

* ***Oracle.JS*** https://github.com/plasmadlt/plasmadlt-invest-fund/blob/master/src/oracle/oracle.js

 This code, based on JS and written with PlasmaJS library, once per day (timeout = 24h) executes reward action of some smart-contract. If you connect all the elements - bank account, smart-contract, responsible for rewards processing, oracle service - for rewards execution, fully self-sufficient invest-found system coulb be build.

* ***PlasmaJS*** https://github.com/plasmadlt/PlasmaJS


## Asset Exchange

PlasmaPay netwotk contains special smart-contracts, needed for assets exchange, necessary transfers and forex operations. Based on this contracts, invest fund operations, related to token exchange - could be easily executed and applied. The way our platform uses it, connected with investments operations - buy / sell various sets of tokens, for example - gambling protocols, etc..

Two main primitives are implemented on PlasmaPay platform - plasma.orderbook and plasma.forex exchagnes protocols.
Let us demostrate the principals, connected with plasma.orderbook exchange protocol.
In general, the following necessary API calls are introduced for this smart contract:

***Setting an order to buy arbitrary tokens at a price set by the user***

***void bid(ion::name user, std::string amount, uint64_t rate, uint64_t precision, ion::symbol_code smbl_code, bool paySysCms)***

```
*ion::name user - A user who wants to purchase certain types of tokens.*

*std::string amount - The number and symbol of tokens for the transaction that the user is ready to buy, in the format ion::big_asset.*

*uint64_t rate - Rate at which the user is ready to buy tokens, value.*

*uint64_t precision - Rate at which the user is ready to buy tokens, accuracy.*

*ion::symbol_code smbl_code - Token symbol that the user offers as a payment for the token that interests him.*
```
***Setting an order to sell arbitrary tokens at a price set by the user.***

***void ask(ion::name user, std::string amount, uint64_t rate, uint64_t precision, ion::symbol_code smbl_code, bool paySysCms)***
```
*ion::name user - A user who wants to sell tokens of a certain type.*

*std::string amount - The number and symbol of tokens for the transaction that the user is willing to sell, in the format ion::big_asset.*

*uint64_t rate - Rate at which the user is ready to sell tokens, value.*

*uint64_t precision - Rate at which the user is ready to sell tokens, accuracy.*

*ion::symbol_code smbl_code - Token symbol for which the user exchanges (sells) their tokens, interest.*

***Setting an order to buy arbitrary tokens at a market price.***

***void bidmarket(ion::name user, std::string amount, ion::symbol_code smbl_code, bool paySysCms);***

*ion::name user - A user who wants to purchase certain types of tokens.*

*std::string amount - The number and symbol of tokens for the transaction that the user is ready to buy, in the format ion::big_asset.*

*ion::symbol_code smbl_code - Token symbol that the user offers as a payment for the token that interests him.*

***Setting an order to sell arbitrary tokens at a market price.***

***void askmarket(ion::name user, std::string amount, ion::symbol_code smbl_code, bool paySysCms);***

*ion::name user - A user who wants to sell tokens of a certain type.*

*std::string amount - The number and symbol of tokens for the transaction that the user is willing to sell, in the format ion::big_asset.*

*ion::symbol_code smbl_code - Token symbol for which the user exchanges (sells) their tokens, interest.*

Based on this API calls, we could implement bash scrips - to provide buy / sell operations for invest tokens.
Below, please, find and example

( # place order -> bank is ready to sell tokens )
* docker exec -i <network> sol --url  --wallet-url  push action plasma.fxob ask '["bank.gmsp", "2.0000 GMSP", "1000", "0", "USDP", "1"]' -p bank.gmsp@active*

( # place order -> user is interested to buy some tokens )
* docker exec -i <network> sol --url  --wallet-url  push action plasma.fxob bid '["someuser", "1.0000 GMSP", "1000", "0", "USDP", "1"]' -p someuser@active*

( # please, execute orders )
* docker exec -i <network> sol --url  --wallet-url  push action plasma.fxob process '["ID_1", "ID_2"]' -p plasma.fxob@active*

This is a brief sample, demonstrating how to execute invest tokens exchange on PlasmaPay platform.
Actually, various combinations could be implemented, depending on your needs and ideas.

```

## Voiting systems for project management -  DAO


### Delegate Selection

<img align="сenter" width="360" height="170" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/voted.png"> </br>

Investors conduct voting for the choice of a delegate by a single vote.

* Voting for candidate selection;
* Voting for the exclusion of a candidate;
* Voting for exceptions to the investment strategy;
* Receiving dividends.

### Delegates voting management

<img align="сenter" width="360" height="170" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/voted2.png"> </br>

Delegates manage the investment fund and make decisions by voting ⅔ of all delegates.

* Analytics invest offers;
* Building investment strategies;
* Asset inclusion management;
* Management of asset allocation in investment offers;
* Financial flow management;
* Management in protocol code change.

 PlasmaPay platform implements the multisig mechanism, to provide delegates voting management. Multisig is a term frequently used in the cryptographic and blockchain space. Essentially it enables multiple parties to sign or approve an action that takes place - typically a requirement for certain wallets, accounts, and smart contracts to prevent a rogue or hacked individual from performing detrimental actions. This allows us to manage invest found's delegates. Each transaction, related to voting or applying investment strategies, could be configured via multisig investment strategies. Let's have a look at example.

Lets assume we have four accounts created on the network:

 * mymultisig11 - a multisig account we will configure
 * partner11111 - first personal account
 * partner22222 - second personal account
 * partner33333 - third personal account

Bash example - how to configure execution

```
docker exec -i <network> sol --url  --wallet-url set account permission mymultisig11 active '{"threshold":2,"keys":[],"accounts":[{"permission":{"actor":"partner11111","permission":"active"},"weight":1},{"permission":{"actor":"partner22222","permission":"active"},"weight":1},{"permission":{"actor":"partner33333","permission":"active"},"weight":1}],"waits":[]}' owner -p mymultisig11@owner
```

Proposal - let's make an investment or vote for delegate
```

docker exec -i <network> sol --url  --wallet-url  multisig propose payme '[{"actor": "partner22222", "permission": "active"},{"actor": "partner33333", "permission": "active"}]' '[{"actor": "mymultisig11", "permission": "active"}]' ion.token transfer '{"from":"mymultisig11", "to":"partner11111", "quantity":"25.0000 GMSP", "memo":"Pay partner11111 some money"}' -p partner11111@active
```
Ok, I agree and gonna approve
```
docker exec -i <network> sol --url  --wallet-url   multisig approve partner11111 payme '{"actor": "partner22222", "permission": "active"}' -p partner22222@active
```
Now that the multisig transaction is approved and user can execute it.
```
docker exec -i <network> sol --url  --wallet-url multisig exec partner11111 payme -p partner11111@active
```

## External data management system

### Orcale.JS Setup

Let's have a look - how typical oracle web-service execution works. The process could be separated into the following steps

 * Dependencies and packages install
 * Setup necessary configuration data
 * Oracle module run

 Firstly, execute the following command -
 npm install (in package directory, no arguments): Install the dependencies in the local node_modules folder.
 This allows all the neccesary files and packages to be installed, required for oracle module.

 Then, have a look at the config file example -
* ***Config js*** https://github.com/plasmadlt/plasmadlt-invest-fund/edit/master/src/config/config.js

 You should setup appropriate parameters, connected w.r.t your network and smart-contract dara.

 * ***chainId*** - hash representing the ID of the chain

 * ***httpEndpoint*** -  the corresponding value is the API endpoint

 * ***updateInterval*** - oracle service repeat time

 * ***account, contract, key*** - smart-contract namings, required for actions execution, for example - transfer or reward.

 And the last step - oracle module run.

 One simple command -> node oracle.js, and you plasma web service is running.
**Docker**
```
git clone https://github.com/plasmadlt/plasmadlt-invest-fund/blob/master/src/oracle/
cd oracle
// install node modules
// install PlasmaJS
docker run -it -v "$PWD":/app -w /app node:latest npm -i
// run oracle
docker run -it -v "$PWD":/app -d --restart unless-stopped -w /app node:latest node
 ```
For better integration, data protection, privacy and safety reasons, you are obliged to apply some third-party software, such as Docker, Cubernetes, to embed your service into.


## Referral Loyalty System

The Referral protocol is a modular solution for setting up a referral system that allows you to create a multi-level system where the affiliate attracts new buyers and referrals using the generated link, distributing it on their social networks, instant messengers and among friends, which will allow you to receive a certain percentage from the purchase of goods from the attracted user, each attracted referral which will attract new customers will also generate rewards to its affiliate. This system works on a chain of blocks (blockchain) where each transaction is tracked with the help of which it is easy to determine the sequence of the referral system.

<img align="сenter" width="420" height="390" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/referral.png"> </br>

includes:


* Use of 42 fiat currencies PlasmaDLT
* Registration and wallet
* Consensual Voting and the Selection of Delegates
* Multi-level reward system
* Adding referral programs
* Reward Percentage Configuration
* Adding Traditional Products
* Creating Tokenized Products

### The principle of the referral system

<img align="left" width="220" height="500" src="https://github.com/plasmadlt/plasmadlt-invest-fund/raw/master/img/referral2.png"> </br>

For more information on working with the registration process API:  

* **PlasmaPay API** https://developer.plasmapay.com/dapp.html
* **PlasmaDLT API** https://developer.plasmapay.com/chain.html
* **Refferal Program Contract** SOON !

1. **Affiliate**: Register on the site of the **Fund website**,
**Fund website** creates an **Affiliate** account (wallet) in the Plasma DLT system.
2. **Affiliate**: creates his own unique link in the personal account of the site
3. **Referral** follows the link performing an action (registration)
4. **Fund website**: sends a JSON transaction to the PlasmaDLT system with parameters from the fund’s account, the referral from the account of the affiliate is registered in the contract of the referral program, the affiliate will receive from the fund a percentage of the referral’s investments.
5. **Fund’s website**: will pay% of purchases to the account **Affiliate** from the **Referral** account
6. **Affiliate**:  will send% of the proceeds from Referrals to its Affiliate

Affiliate rewards are multi-level not only with the purchase of a referral, but also with purchases made by people who use the referral referral link.

---------------------------
