var group__lpspi__driver =
[
    [ "lpspi_master_config_t", "group__lpspi__driver.html#structlpspi__master__config__t", [
      [ "baudRate", "group__lpspi__driver.html#ab38a80feace530cdca66134f6e3801aa", null ],
      [ "betweenTransferDelayInNanoSec", "group__lpspi__driver.html#a0c9513415b6b6dc15b32854a9c9d9ef9", null ],
      [ "bitsPerFrame", "group__lpspi__driver.html#a8ccf58110b76fd897fd5861ec36ba249", null ],
      [ "cpha", "group__lpspi__driver.html#a6a5bc23653684a0137bc4ee8015a9766", null ],
      [ "cpol", "group__lpspi__driver.html#a0fb0eb4a83201ec6084022aeddc21780", null ],
      [ "dataOutConfig", "group__lpspi__driver.html#a7dbd7d9fb1c0e29e8e4c45d6707a50d5", null ],
      [ "direction", "group__lpspi__driver.html#a298fb139762c91fe1195f1cac7119d7e", null ],
      [ "lastSckToPcsDelayInNanoSec", "group__lpspi__driver.html#a9aa3ebdf191b0c2147755066f452b9c9", null ],
      [ "pcsActiveHighOrLow", "group__lpspi__driver.html#acd4f574514beb757a0f2016013190142", null ],
      [ "pcsToSckDelayInNanoSec", "group__lpspi__driver.html#a90f1390d2fa2a0e5f08925628f2fb227", null ],
      [ "pinCfg", "group__lpspi__driver.html#a0a8703742c1fd11af34757242016106f", null ],
      [ "whichPcs", "group__lpspi__driver.html#a78bb6fb8fb2066e093fcfa54b6c4503c", null ]
    ] ],
    [ "lpspi_slave_config_t", "group__lpspi__driver.html#structlpspi__slave__config__t", [
      [ "bitsPerFrame", "group__lpspi__driver.html#a8ccf58110b76fd897fd5861ec36ba249", null ],
      [ "cpha", "group__lpspi__driver.html#a6a5bc23653684a0137bc4ee8015a9766", null ],
      [ "cpol", "group__lpspi__driver.html#a0fb0eb4a83201ec6084022aeddc21780", null ],
      [ "dataOutConfig", "group__lpspi__driver.html#a7dbd7d9fb1c0e29e8e4c45d6707a50d5", null ],
      [ "direction", "group__lpspi__driver.html#a298fb139762c91fe1195f1cac7119d7e", null ],
      [ "pcsActiveHighOrLow", "group__lpspi__driver.html#acd4f574514beb757a0f2016013190142", null ],
      [ "pinCfg", "group__lpspi__driver.html#a0a8703742c1fd11af34757242016106f", null ],
      [ "whichPcs", "group__lpspi__driver.html#a78bb6fb8fb2066e093fcfa54b6c4503c", null ]
    ] ],
    [ "lpspi_transfer_t", "group__lpspi__driver.html#structlpspi__transfer__t", [
      [ "configFlags", "group__lpspi__driver.html#a8f596820084347c93c458b7553bdd067", null ],
      [ "dataSize", "group__lpspi__driver.html#aec81567ca73e5b0cb790098785e345c5", null ],
      [ "rxData", "group__lpspi__driver.html#ab83c0e07099df7beb8e491cb91914de0", null ],
      [ "txData", "group__lpspi__driver.html#a03c054bb486fb65133eb9f6849266fb1", null ]
    ] ],
    [ "lpspi_master_handle_t", "group__lpspi__driver.html#struct__lpspi__master__handle", [
      [ "base", "group__lpspi__driver.html#ad8c938c2c7cdd5c7feabd220911f8350", null ],
      [ "bytesEachRead", "group__lpspi__driver.html#a480857e72ca27c2cd2ad308f8a0e7993", null ],
      [ "bytesEachWrite", "group__lpspi__driver.html#aa6f46bac700151385f8063c97b21d692", null ],
      [ "callback", "group__lpspi__driver.html#a072fc39e6140224fedd028ce727c7aca", null ],
      [ "fifoSize", "group__lpspi__driver.html#a1e4dd1f7e153c765af264d2efad25cd5", null ],
      [ "isByteSwap", "group__lpspi__driver.html#a588598f72e912656596294358aab6fe2", null ],
      [ "isPcsContinuous", "group__lpspi__driver.html#a8f0b46b9c899a9e4c20a600974af98fc", null ],
      [ "readRegRemainingTimes", "group__lpspi__driver.html#aac4f8bb4a502e020b3d91cc2aa93a98d", null ],
      [ "rxData", "group__lpspi__driver.html#aa58335de5bfa8923228432b62ea9308a", null ],
      [ "rxRemainingByteCount", "group__lpspi__driver.html#a4ae23f3b283c257a77e626702335b56d", null ],
      [ "rxWatermark", "group__lpspi__driver.html#a91639d4f66a8980e9ef3bec6bf845b35", null ],
      [ "state", "group__lpspi__driver.html#a06fcd46097cb1779eaa383a6419cd27d", null ],
      [ "totalByteCount", "group__lpspi__driver.html#a28686689a3803230c7fe2658c93eac50", null ],
      [ "txBuffIfNull", "group__lpspi__driver.html#ad0c00ea960d53424d98de2882a50048d", null ],
      [ "txData", "group__lpspi__driver.html#ab56d8f300582ce9d7f4a79729124739d", null ],
      [ "txRemainingByteCount", "group__lpspi__driver.html#a7794f7cce2e0b6a4f0699a8c0ef5bc37", null ],
      [ "userData", "group__lpspi__driver.html#a2e294dd14122c554baa0665072b4ca7a", null ],
      [ "writeRegRemainingTimes", "group__lpspi__driver.html#a67e97f14865710b9db144898df46c804", null ],
      [ "writeTcrInIsr", "group__lpspi__driver.html#aa5570f840f4056d62c203fc5c1b590b1", null ]
    ] ],
    [ "lpspi_slave_handle_t", "group__lpspi__driver.html#struct__lpspi__slave__handle", [
      [ "base", "group__lpspi__driver.html#ad8c938c2c7cdd5c7feabd220911f8350", null ],
      [ "bytesEachRead", "group__lpspi__driver.html#a480857e72ca27c2cd2ad308f8a0e7993", null ],
      [ "bytesEachWrite", "group__lpspi__driver.html#aa6f46bac700151385f8063c97b21d692", null ],
      [ "callback", "group__lpspi__driver.html#afc8921cd2f17ad5d419f3ecfc5df7cc7", null ],
      [ "errorCount", "group__lpspi__driver.html#a2a11c9c06fe4f8a45030f131e5800ae4", null ],
      [ "fifoSize", "group__lpspi__driver.html#a1e4dd1f7e153c765af264d2efad25cd5", null ],
      [ "isByteSwap", "group__lpspi__driver.html#a588598f72e912656596294358aab6fe2", null ],
      [ "readRegRemainingTimes", "group__lpspi__driver.html#aac4f8bb4a502e020b3d91cc2aa93a98d", null ],
      [ "rxData", "group__lpspi__driver.html#aa58335de5bfa8923228432b62ea9308a", null ],
      [ "rxRemainingByteCount", "group__lpspi__driver.html#a4ae23f3b283c257a77e626702335b56d", null ],
      [ "rxWatermark", "group__lpspi__driver.html#a91639d4f66a8980e9ef3bec6bf845b35", null ],
      [ "state", "group__lpspi__driver.html#a06fcd46097cb1779eaa383a6419cd27d", null ],
      [ "totalByteCount", "group__lpspi__driver.html#a28686689a3803230c7fe2658c93eac50", null ],
      [ "txData", "group__lpspi__driver.html#ab56d8f300582ce9d7f4a79729124739d", null ],
      [ "txRemainingByteCount", "group__lpspi__driver.html#a7794f7cce2e0b6a4f0699a8c0ef5bc37", null ],
      [ "userData", "group__lpspi__driver.html#a2e294dd14122c554baa0665072b4ca7a", null ],
      [ "writeRegRemainingTimes", "group__lpspi__driver.html#a67e97f14865710b9db144898df46c804", null ]
    ] ],
    [ "lpspi_master_transfer_callback_t", "group__lpspi__driver.html#ga65b6cc7e0ab88322b8c87957c855b595", null ],
    [ "lpspi_slave_transfer_callback_t", "group__lpspi__driver.html#ga5f085dc3448a6b1d5ab388ac5ce90573", null ],
    [ "_lpspi_dma_enable", "group__lpspi__driver.html#gafed26b4ba584824e51e91b4040591cf2", [
      [ "kLPSPI_TxDmaEnable", "group__lpspi__driver.html#ggafed26b4ba584824e51e91b4040591cf2a527e96eef74618b0b40c30cf6a1a2828", null ],
      [ "kLPSPI_RxDmaEnable", "group__lpspi__driver.html#ggafed26b4ba584824e51e91b4040591cf2aea817767e6bd800ff275458f07f363db", null ]
    ] ],
    [ "_lpspi_flags", "group__lpspi__driver.html#gad97e399bf4883a243d83fc7cffb19655", [
      [ "kLPSPI_TxDataRequestFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655a3947665fd37fb039123f594df926cff1", null ],
      [ "kLPSPI_RxDataReadyFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655a5bdd7020ceafc2b5cbfa6e9ffa72b1cb", null ],
      [ "kLPSPI_WordCompleteFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655ad84b2113adf471177ecee7d7de5f82e0", null ],
      [ "kLPSPI_FrameCompleteFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655acec0a8ef85d641ef6589d4deea14ce21", null ],
      [ "kLPSPI_TransferCompleteFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655a4c1300adf80a19668a729a9b9f1c3660", null ],
      [ "kLPSPI_TransmitErrorFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655a240267c0100041bbeb6acbae45a37b15", null ],
      [ "kLPSPI_ReceiveErrorFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655aad86acfadef3dc8df91849884ec355e3", null ],
      [ "kLPSPI_DataMatchFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655a53fa68713ae51b053362e99930b1f841", null ],
      [ "kLPSPI_ModuleBusyFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655a71a15d927635fc51125dadf7ad1167a8", null ],
      [ "kLPSPI_AllStatusFlag", "group__lpspi__driver.html#ggad97e399bf4883a243d83fc7cffb19655af29f28d13e798c1fcbce009e203a1fed", null ]
    ] ],
    [ "_lpspi_interrupt_enable", "group__lpspi__driver.html#gab80d8a605a7ba992043ba4e6afa501a3", [
      [ "kLPSPI_TxInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3a2d20e000503ba5c5a0c9f67c60a714cd", null ],
      [ "kLPSPI_RxInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3a2b9ff66ccb9229355668bdcc05f77dc9", null ],
      [ "kLPSPI_WordCompleteInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3a73f0e5f45806e247e46bf7244695693e", null ],
      [ "kLPSPI_FrameCompleteInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3a0c0dde3048f3d25c56eac65acaceb49b", null ],
      [ "kLPSPI_TransferCompleteInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3ac0d5fa696784facb2fbaf2c01e7569bd", null ],
      [ "kLPSPI_TransmitErrorInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3a23f8ac8e04b9cd32f458727ec1ed38ad", null ],
      [ "kLPSPI_ReceiveErrorInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3a0433263f892d70eb2859746b075c14e7", null ],
      [ "kLPSPI_DataMatchInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3a6032909768af91efcdb432843f48047b", null ],
      [ "kLPSPI_AllInterruptEnable", "group__lpspi__driver.html#ggab80d8a605a7ba992043ba4e6afa501a3a2a8a671a096982bdf93ddba6d146d5d6", null ]
    ] ],
    [ "_lpspi_pcs_polarity", "group__lpspi__driver.html#ga69d39d2c7c0054aa76e8f3282c98cc43", [
      [ "kLPSPI_Pcs0ActiveLow", "group__lpspi__driver.html#gga69d39d2c7c0054aa76e8f3282c98cc43a39ba76078eacda5cd1067083e1424219", null ],
      [ "kLPSPI_Pcs1ActiveLow", "group__lpspi__driver.html#gga69d39d2c7c0054aa76e8f3282c98cc43a9fba36c05ea23b988a6d6eea57111cc4", null ],
      [ "kLPSPI_Pcs2ActiveLow", "group__lpspi__driver.html#gga69d39d2c7c0054aa76e8f3282c98cc43a59994c42bc8d6a84754db3eb615b9a52", null ],
      [ "kLPSPI_Pcs3ActiveLow", "group__lpspi__driver.html#gga69d39d2c7c0054aa76e8f3282c98cc43a7d590e420c3d77192425d459ef47cb18", null ],
      [ "kLPSPI_PcsAllActiveLow", "group__lpspi__driver.html#gga69d39d2c7c0054aa76e8f3282c98cc43a7bfc7ab3ae077df8f7dedd69caefa159", null ]
    ] ],
    [ "_lpspi_status", "group__lpspi__driver.html#ga8e41dbbd251f8207dab31385701c4f50", [
      [ "kStatus_LPSPI_Busy", "group__lpspi__driver.html#gga8e41dbbd251f8207dab31385701c4f50a7f12633826bd7df839619b14c0ca28cc", null ],
      [ "kStatus_LPSPI_Error", "group__lpspi__driver.html#gga8e41dbbd251f8207dab31385701c4f50a3faf60052aef160c9e665b923f6560f0", null ],
      [ "kStatus_LPSPI_Idle", "group__lpspi__driver.html#gga8e41dbbd251f8207dab31385701c4f50a44467ff9577a1be6b13121e8f075d92a", null ],
      [ "kStatus_LPSPI_OutOfRange", "group__lpspi__driver.html#gga8e41dbbd251f8207dab31385701c4f50a2f2d2fc26087dd6282b229e1c7471758", null ]
    ] ],
    [ "_lpspi_transfer_config_flag_for_master", "group__lpspi__driver.html#ga8c2566783079ecdbb478f06658375005", [
      [ "kLPSPI_MasterPcs0", "group__lpspi__driver.html#gga8c2566783079ecdbb478f06658375005ad472cdb233d16b4b9e5372c214e34a3c", null ],
      [ "kLPSPI_MasterPcs1", "group__lpspi__driver.html#gga8c2566783079ecdbb478f06658375005a1b57aa21038a9d2fe7affdda155a21d0", null ],
      [ "kLPSPI_MasterPcs2", "group__lpspi__driver.html#gga8c2566783079ecdbb478f06658375005abd22976ae5150a0f57f27f439d25e6d0", null ],
      [ "kLPSPI_MasterPcs3", "group__lpspi__driver.html#gga8c2566783079ecdbb478f06658375005a38ce619f68339f607e63affd7ce012a5", null ],
      [ "kLPSPI_MasterPcsContinuous", "group__lpspi__driver.html#gga8c2566783079ecdbb478f06658375005a81e8942cb9a3dc01b6900fa0fc44a807", null ],
      [ "kLPSPI_MasterByteSwap", "group__lpspi__driver.html#gga8c2566783079ecdbb478f06658375005aada04eea6a730a7536682944531385bb", null ]
    ] ],
    [ "_lpspi_transfer_config_flag_for_slave", "group__lpspi__driver.html#gaf3ef07696513a970ce8195b5b0f1a8c1", [
      [ "kLPSPI_SlavePcs0", "group__lpspi__driver.html#ggaf3ef07696513a970ce8195b5b0f1a8c1ab1faad46d523e037048a3064893ae07c", null ],
      [ "kLPSPI_SlavePcs1", "group__lpspi__driver.html#ggaf3ef07696513a970ce8195b5b0f1a8c1a0e6aee8fe7dfd9c2d66b505d73c37232", null ],
      [ "kLPSPI_SlavePcs2", "group__lpspi__driver.html#ggaf3ef07696513a970ce8195b5b0f1a8c1ae64e50be4483554dc3ebc66c379de03e", null ],
      [ "kLPSPI_SlavePcs3", "group__lpspi__driver.html#ggaf3ef07696513a970ce8195b5b0f1a8c1a6d5cce71f6a0551128e551100bc9f39f", null ],
      [ "kLPSPI_SlaveByteSwap", "group__lpspi__driver.html#ggaf3ef07696513a970ce8195b5b0f1a8c1a42d91e6c56fda80853954fdf01365998", null ]
    ] ],
    [ "_lpspi_transfer_state", "group__lpspi__driver.html#ga7718265fdc39522b101e1deb430ab1f7", [
      [ "kLPSPI_Idle", "group__lpspi__driver.html#gga7718265fdc39522b101e1deb430ab1f7ad1366ce0c1c0c8a66a6ee9611cb4ae8c", null ],
      [ "kLPSPI_Busy", "group__lpspi__driver.html#gga7718265fdc39522b101e1deb430ab1f7a81465b4e8946a9a8b3634e4fc04933fd", null ],
      [ "kLPSPI_Error", "group__lpspi__driver.html#gga7718265fdc39522b101e1deb430ab1f7a9f52ab17cca4320266e1b7c194df33ec", null ]
    ] ],
    [ "lpspi_clock_phase_t", "group__lpspi__driver.html#ga00a7c64b74442ff1961346c0297f9ab3", [
      [ "kLPSPI_ClockPhaseFirstEdge", "group__lpspi__driver.html#gga00a7c64b74442ff1961346c0297f9ab3a1c127121f13c6756c19c6640a1a3f66f", null ],
      [ "kLPSPI_ClockPhaseSecondEdge", "group__lpspi__driver.html#gga00a7c64b74442ff1961346c0297f9ab3a69541d5ec76b63987c1523f67f281039", null ]
    ] ],
    [ "lpspi_clock_polarity_t", "group__lpspi__driver.html#gaafc42f4a3c8eb16d4777f3c6f0f8654c", [
      [ "kLPSPI_ClockPolarityActiveHigh", "group__lpspi__driver.html#ggaafc42f4a3c8eb16d4777f3c6f0f8654ca5f5af0b1696c75bddcc45548dc6eb4e5", null ],
      [ "kLPSPI_ClockPolarityActiveLow", "group__lpspi__driver.html#ggaafc42f4a3c8eb16d4777f3c6f0f8654ca8d0257641a93e1539be2284aa8dea2c2", null ]
    ] ],
    [ "lpspi_data_out_config_t", "group__lpspi__driver.html#ga134cbe42b20647e752e66aaeabbc10d4", [
      [ "kLpspiDataOutRetained", "group__lpspi__driver.html#gga134cbe42b20647e752e66aaeabbc10d4a82a3d2bf52e339c016ea5b55b6e5a0b5", null ],
      [ "kLpspiDataOutTristate", "group__lpspi__driver.html#gga134cbe42b20647e752e66aaeabbc10d4ad88e6541ea02827476f10ca3a7906129", null ]
    ] ],
    [ "lpspi_delay_type_t", "group__lpspi__driver.html#gae5e0bf71f3d28f35327f0268039d0c0c", [
      [ "kLPSPI_PcsToSck", "group__lpspi__driver.html#ggae5e0bf71f3d28f35327f0268039d0c0ca3d71d8a9758a52226844e7b721f3dfb8", null ],
      [ "kLPSPI_LastSckToPcs", "group__lpspi__driver.html#ggae5e0bf71f3d28f35327f0268039d0c0ca4c475db384f87476967ad8318fc8e941", null ],
      [ "kLPSPI_BetweenTransfer", "group__lpspi__driver.html#ggae5e0bf71f3d28f35327f0268039d0c0caec200ab5e56e72854f694bc65846e015", null ]
    ] ],
    [ "lpspi_host_request_select_t", "group__lpspi__driver.html#ga9179eac6fe5a70f9350df669a4547b57", [
      [ "kLPSPI_HostReqExtPin", "group__lpspi__driver.html#gga9179eac6fe5a70f9350df669a4547b57a1ecf2a9ee61a10a6abfd3b003ecded95", null ],
      [ "kLPSPI_HostReqInternalTrigger", "group__lpspi__driver.html#gga9179eac6fe5a70f9350df669a4547b57ae7bcf394055c5c96962fbdeb59473b53", null ]
    ] ],
    [ "lpspi_master_slave_mode_t", "group__lpspi__driver.html#gae28cea6ce513555e39a3ac343d05ad52", [
      [ "kLPSPI_Master", "group__lpspi__driver.html#ggae28cea6ce513555e39a3ac343d05ad52a5f5755c293c4eea06b35528c7dadb505", null ],
      [ "kLPSPI_Slave", "group__lpspi__driver.html#ggae28cea6ce513555e39a3ac343d05ad52ac2fbf07d3dcc5fd91629c58bec8aa5c4", null ]
    ] ],
    [ "lpspi_match_config_t", "group__lpspi__driver.html#gac44bb22e39759dab2695974b9e232396", [
      [ "kLPSI_MatchDisabled", "group__lpspi__driver.html#ggac44bb22e39759dab2695974b9e232396a05d1b5c903dfe4898c9b1fd684250294", null ],
      [ "kLPSI_1stWordEqualsM0orM1", "group__lpspi__driver.html#ggac44bb22e39759dab2695974b9e232396a17bfedfd52cb4ad0b4806b0867a04e89", null ],
      [ "kLPSI_AnyWordEqualsM0orM1", "group__lpspi__driver.html#ggac44bb22e39759dab2695974b9e232396ae98eab6b132ff11c1df102e8e6cdd24c", null ],
      [ "kLPSI_1stWordEqualsM0and2ndWordEqualsM1", "group__lpspi__driver.html#ggac44bb22e39759dab2695974b9e232396a11c22b22c672c03591c560a6c8faf428", null ],
      [ "kLPSI_AnyWordEqualsM0andNxtWordEqualsM1", "group__lpspi__driver.html#ggac44bb22e39759dab2695974b9e232396a67938e63bf8168ce35e090a2b210ad2e", null ],
      [ "kLPSI_1stWordAndM1EqualsM0andM1", "group__lpspi__driver.html#ggac44bb22e39759dab2695974b9e232396a20ae6796a58bde43ba80737927e905ab", null ],
      [ "kLPSI_AnyWordAndM1EqualsM0andM1", "group__lpspi__driver.html#ggac44bb22e39759dab2695974b9e232396a02b507b2df58ba42c650727fc0a1cfa5", null ]
    ] ],
    [ "lpspi_pcs_polarity_config_t", "group__lpspi__driver.html#ga6303bce5095876c64d47e3b19e76bd97", [
      [ "kLPSPI_PcsActiveHigh", "group__lpspi__driver.html#gga6303bce5095876c64d47e3b19e76bd97a5be0e938a788cff5717c2c2590e52c59", null ],
      [ "kLPSPI_PcsActiveLow", "group__lpspi__driver.html#gga6303bce5095876c64d47e3b19e76bd97a4a1448bee9f6f3d4383fe13cdc1100ce", null ]
    ] ],
    [ "lpspi_pin_config_t", "group__lpspi__driver.html#gae5ea17a161935f47c786934c524bb2af", [
      [ "kLPSPI_SdiInSdoOut", "group__lpspi__driver.html#ggae5ea17a161935f47c786934c524bb2afa25d21ca2f0397f7bf6c23a1b1c6691f7", null ],
      [ "kLPSPI_SdoInSdoOut", "group__lpspi__driver.html#ggae5ea17a161935f47c786934c524bb2afa33c599830166b775f368ee16ff0682d5", null ],
      [ "kLPSPI_SdiInSdiOut", "group__lpspi__driver.html#ggae5ea17a161935f47c786934c524bb2afa1e5af86e47569305db258791cb467d30", null ],
      [ "kLPSPI_SdoInSdiOut", "group__lpspi__driver.html#ggae5ea17a161935f47c786934c524bb2afa43f7557904b7103eeb4516624d0c995c", null ]
    ] ],
    [ "lpspi_shift_direction_t", "group__lpspi__driver.html#ga4116edfccfda3a0788a9b68bb9b50fcd", [
      [ "kLPSPI_MsbFirst", "group__lpspi__driver.html#gga4116edfccfda3a0788a9b68bb9b50fcda6cfcf70021ed17b06148973a577b06b0", null ],
      [ "kLPSPI_LsbFirst", "group__lpspi__driver.html#gga4116edfccfda3a0788a9b68bb9b50fcdaa258be180c87a702892e74e80612bcac", null ]
    ] ],
    [ "lpspi_transfer_width_t", "group__lpspi__driver.html#gaa5d9038e390c8a7610dc72375da252a7", [
      [ "kLPSPI_SingleBitXfer", "group__lpspi__driver.html#ggaa5d9038e390c8a7610dc72375da252a7a56986005418db6d0910782c58ed92dc0", null ],
      [ "kLPSPI_TwoBitXfer", "group__lpspi__driver.html#ggaa5d9038e390c8a7610dc72375da252a7aeb5365dd5861043f098db28e9945c191", null ],
      [ "kLPSPI_FourBitXfer", "group__lpspi__driver.html#ggaa5d9038e390c8a7610dc72375da252a7a591c0c33b13b3fc9fe8d05bb14e5176a", null ]
    ] ],
    [ "lpspi_which_pcs_t", "group__lpspi__driver.html#ga90ad4c281c99433627f8cccf56b2a653", [
      [ "kLPSPI_Pcs0", "group__lpspi__driver.html#gga90ad4c281c99433627f8cccf56b2a653ad0a33b6673cd3a9e54ab55f5d5138871", null ],
      [ "kLPSPI_Pcs1", "group__lpspi__driver.html#gga90ad4c281c99433627f8cccf56b2a653a276b09136d3d15a0fe0dc5d0bab9b3f1", null ],
      [ "kLPSPI_Pcs2", "group__lpspi__driver.html#gga90ad4c281c99433627f8cccf56b2a653a2d4d2611c76b7832b346d00072f49561", null ],
      [ "kLPSPI_Pcs3", "group__lpspi__driver.html#gga90ad4c281c99433627f8cccf56b2a653a91ecfb74e3c582725faea8aa28700590", null ]
    ] ],
    [ "LPSPI_ClearStatusFlags", "group__lpspi__driver.html#ga46f471b0b317dbcefb753ac1eca220cc", null ],
    [ "LPSPI_Deinit", "group__lpspi__driver.html#gaec14fb9cf6f33a9482cad1ac3367ceeb", null ],
    [ "LPSPI_DisableDMA", "group__lpspi__driver.html#gae40bb751eb579a3ba6f0df9d2b128074", null ],
    [ "LPSPI_DisableInterrupts", "group__lpspi__driver.html#ga40a046e84442cb6f187f37b676a026cc", null ],
    [ "LPSPI_Enable", "group__lpspi__driver.html#ga7652e02b7e15dbbe611bf1b88aa6f658", null ],
    [ "LPSPI_EnableDMA", "group__lpspi__driver.html#ga962cc835d0c6133d3b5ca97103ffb3fb", null ],
    [ "LPSPI_EnableInterrupts", "group__lpspi__driver.html#ga4808761455aaf83e91fd8379874946ed", null ],
    [ "LPSPI_FlushFifo", "group__lpspi__driver.html#ga1388a83ff99459ea04927a951fe4ba64", null ],
    [ "LPSPI_GetRxFifoCount", "group__lpspi__driver.html#gaccf9caba656fbab8c2baaf9c064dfd18", null ],
    [ "LPSPI_GetRxFifoSize", "group__lpspi__driver.html#ga06d5b0b646c41f819d66c570abe82686", null ],
    [ "LPSPI_GetRxRegisterAddress", "group__lpspi__driver.html#ga441f4a34fc1014e80df6dbdd3ccef49e", null ],
    [ "LPSPI_GetStatusFlags", "group__lpspi__driver.html#ga65f275a2b7c4c85e65f66dc205ccaba2", null ],
    [ "LPSPI_GetTxFifoCount", "group__lpspi__driver.html#gaad302d78079501338706a15b2a25b627", null ],
    [ "LPSPI_GetTxFifoSize", "group__lpspi__driver.html#gaa8de4de520051c5d597c187c83a716fe", null ],
    [ "LPSPI_GetTxRegisterAddress", "group__lpspi__driver.html#gad411d09a6ece1909f3fa0c6eb6972a27", null ],
    [ "LPSPI_IsMaster", "group__lpspi__driver.html#gaf0a22161d44cf08f3609ce0371190b43", null ],
    [ "LPSPI_MasterAbortTransfer", "group__lpspi__driver.html#gac66232f8876a20334a9c01cfd83a4bce", null ],
    [ "LPSPI_MasterCreateHandle", "group__lpspi__driver.html#ga81ce64b08a05cb34fe8416c9fc2c969f", null ],
    [ "LPSPI_MasterGetDefaultConfig", "group__lpspi__driver.html#gaf7c865e3ddf8b0e8b39eaa044ebdd7a9", null ],
    [ "LPSPI_MasterGetTransferCount", "group__lpspi__driver.html#ga4ff6873dffb078d1d49532ad0670e405", null ],
    [ "LPSPI_MasterHandleInterrupt", "group__lpspi__driver.html#gaacfd1e61150c8709911fea392e5c8cea", null ],
    [ "LPSPI_MasterInit", "group__lpspi__driver.html#ga22ae05bf7948761752a425f273423af4", null ],
    [ "LPSPI_MasterSetBaudRate", "group__lpspi__driver.html#ga6e952fee44ee7107dd22be1fcca41599", null ],
    [ "LPSPI_MasterSetDelayScaler", "group__lpspi__driver.html#ga9b69797908deb95b2b96e76bc7f8e4f9", null ],
    [ "LPSPI_MasterSetDelayTimes", "group__lpspi__driver.html#ga35f5b5317e3faffe8307221c24c2eeb3", null ],
    [ "LPSPI_MasterTransferBlocking", "group__lpspi__driver.html#ga7397508d8f35bd53d48d2bd400b8855a", null ],
    [ "LPSPI_MasterTransferNonBlocking", "group__lpspi__driver.html#ga962d0a70e661183c6925f87d97ab71d0", null ],
    [ "LPSPI_ReadDataNonBlocking", "group__lpspi__driver.html#gad424e970bbb5333e45eaea2f66885521", null ],
    [ "LPSPI_Reset", "group__lpspi__driver.html#ga65c6f36d3b7c051b2f4c4b3c0f4e67a2", null ],
    [ "LPSPI_SetAllPcsPolarity", "group__lpspi__driver.html#gac44e343cc612a8f9662dca0124e01375", null ],
    [ "LPSPI_SetFifoWatermarks", "group__lpspi__driver.html#ga9036ebfaa63448544b3a15731bf64afb", null ],
    [ "LPSPI_SetFrameSize", "group__lpspi__driver.html#ga1c04805f36ab2d8f3dcf8204ad4e6fc8", null ],
    [ "LPSPI_SetMasterSlaveMode", "group__lpspi__driver.html#ga31dd4286061d9827893b20da53fbe711", null ],
    [ "LPSPI_SlaveAbortTransfer", "group__lpspi__driver.html#gafdd65d9bb5bad35e2566267cc209fbea", null ],
    [ "LPSPI_SlaveCreateHandle", "group__lpspi__driver.html#ga17795aed6614f3d2f449309ad7df1d57", null ],
    [ "LPSPI_SlaveGetDefaultConfig", "group__lpspi__driver.html#ga5c8896fd0d8c76434b74698487f0f838", null ],
    [ "LPSPI_SlaveGetTransferCount", "group__lpspi__driver.html#ga30990cbcf40543dfbc514c11bfb5c4b9", null ],
    [ "LPSPI_SlaveHandleInterrupt", "group__lpspi__driver.html#ga4663d972940c359b6ff968b276a8eb0a", null ],
    [ "LPSPI_SlaveInit", "group__lpspi__driver.html#ga2f690f608d984b845a7bee7a1efae45f", null ],
    [ "LPSPI_SlaveTransferNonBlocking", "group__lpspi__driver.html#ga41d2ccaef2f31a13ce2baef806a7aa2b", null ],
    [ "LPSPI_WriteDataNonBlocking", "group__lpspi__driver.html#ga3c54f5e7381db4f9291ca7f2e74e92d8", null ]
];