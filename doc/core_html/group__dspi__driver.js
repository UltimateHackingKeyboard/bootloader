var group__dspi__driver =
[
    [ "dspi_command_data_config_t", "group__dspi__driver.html#structdspi__command__data__config__t", [
      [ "clearTransferCount", "group__dspi__driver.html#a02c180153476bb2cf8fc561f15672bb9", null ],
      [ "isEndOfQueue", "group__dspi__driver.html#ab8033196bf7f17449d38b1472906c364", null ],
      [ "isPcsContinuous", "group__dspi__driver.html#aff29f3e26c0e3e8fde31f4614bf857a4", null ],
      [ "whichCtar", "group__dspi__driver.html#ac45d6c26892c8389409d760b1df1bb6c", null ],
      [ "whichPcs", "group__dspi__driver.html#a361b1cae3e8ba007b24d3721fc0275d3", null ]
    ] ],
    [ "dspi_master_ctar_config_t", "group__dspi__driver.html#structdspi__master__ctar__config__t", [
      [ "baudRate", "group__dspi__driver.html#ab38a80feace530cdca66134f6e3801aa", null ],
      [ "betweenTransferDelayInNanoSec", "group__dspi__driver.html#a0c9513415b6b6dc15b32854a9c9d9ef9", null ],
      [ "bitsPerFrame", "group__dspi__driver.html#a8ccf58110b76fd897fd5861ec36ba249", null ],
      [ "cpha", "group__dspi__driver.html#af0d368adbb308408dd5363039987896f", null ],
      [ "cpol", "group__dspi__driver.html#a2fe26bcedfe7c42d70ce5937888aedbe", null ],
      [ "direction", "group__dspi__driver.html#a568c1aaf5a6ab0e6d70fbb09e7504ce5", null ],
      [ "lastSckToPcsDelayInNanoSec", "group__dspi__driver.html#a9aa3ebdf191b0c2147755066f452b9c9", null ],
      [ "pcsToSckDelayInNanoSec", "group__dspi__driver.html#a90f1390d2fa2a0e5f08925628f2fb227", null ]
    ] ],
    [ "dspi_master_config_t", "group__dspi__driver.html#structdspi__master__config__t", [
      [ "ctarConfig", "group__dspi__driver.html#a5fe0dea438c0a381fbc560248223ceb2", null ],
      [ "enableContinuousSCK", "group__dspi__driver.html#ae5d5a0d257edd52b39bc7eed2789432a", null ],
      [ "enableModifiedTimingFormat", "group__dspi__driver.html#a9f5693d8510277f6c97e1cdd64fa2a8b", null ],
      [ "enableRxFifoOverWrite", "group__dspi__driver.html#a2a901c97793efe41a681b104173bb395", null ],
      [ "pcsActiveHighOrLow", "group__dspi__driver.html#ad782258c2c9e2c728de750dc18f97a29", null ],
      [ "samplePoint", "group__dspi__driver.html#a8c9eff47b85e5843361534a77d0ec0f4", null ],
      [ "whichCtar", "group__dspi__driver.html#ac45d6c26892c8389409d760b1df1bb6c", null ],
      [ "whichPcs", "group__dspi__driver.html#a361b1cae3e8ba007b24d3721fc0275d3", null ]
    ] ],
    [ "dspi_slave_ctar_config_t", "group__dspi__driver.html#structdspi__slave__ctar__config__t", [
      [ "bitsPerFrame", "group__dspi__driver.html#a8ccf58110b76fd897fd5861ec36ba249", null ],
      [ "cpha", "group__dspi__driver.html#af0d368adbb308408dd5363039987896f", null ],
      [ "cpol", "group__dspi__driver.html#a2fe26bcedfe7c42d70ce5937888aedbe", null ]
    ] ],
    [ "dspi_slave_config_t", "group__dspi__driver.html#structdspi__slave__config__t", [
      [ "ctarConfig", "group__dspi__driver.html#a7490b2e3f16c334bcd2d686b895eb634", null ],
      [ "enableContinuousSCK", "group__dspi__driver.html#ae5d5a0d257edd52b39bc7eed2789432a", null ],
      [ "enableModifiedTimingFormat", "group__dspi__driver.html#a9f5693d8510277f6c97e1cdd64fa2a8b", null ],
      [ "enableRxFifoOverWrite", "group__dspi__driver.html#a2a901c97793efe41a681b104173bb395", null ],
      [ "samplePoint", "group__dspi__driver.html#a8c9eff47b85e5843361534a77d0ec0f4", null ],
      [ "whichCtar", "group__dspi__driver.html#ac45d6c26892c8389409d760b1df1bb6c", null ]
    ] ],
    [ "dspi_transfer_t", "group__dspi__driver.html#structdspi__transfer__t", [
      [ "configFlags", "group__dspi__driver.html#a8f596820084347c93c458b7553bdd067", null ],
      [ "dataSize", "group__dspi__driver.html#aec81567ca73e5b0cb790098785e345c5", null ],
      [ "rxData", "group__dspi__driver.html#ab83c0e07099df7beb8e491cb91914de0", null ],
      [ "txData", "group__dspi__driver.html#a03c054bb486fb65133eb9f6849266fb1", null ]
    ] ],
    [ "dspi_master_handle_t", "group__dspi__driver.html#struct__dspi__master__handle", [
      [ "bitsPerFrame", "group__dspi__driver.html#a8ccf58110b76fd897fd5861ec36ba249", null ],
      [ "callback", "group__dspi__driver.html#a115587f06105cf3be353829d0773cb88", null ],
      [ "command", "group__dspi__driver.html#aaa54e50f47525ba537305a7e551fee60", null ],
      [ "fifoSize", "group__dspi__driver.html#a4c97b51607a7c04eda98c14c23790886", null ],
      [ "isPcsActiveAfterTransfer", "group__dspi__driver.html#a7987be6f0a72e67b2d5f35032409cb62", null ],
      [ "isThereExtraByte", "group__dspi__driver.html#af01b42dfc4c4be3e12be53f4721b6e5a", null ],
      [ "lastCommand", "group__dspi__driver.html#ab21067b70770d32bdc79e90f9a23a9ef", null ],
      [ "remainingReceiveByteCount", "group__dspi__driver.html#afeddb18283b63e45997bdd7cae9a698e", null ],
      [ "remainingSendByteCount", "group__dspi__driver.html#a661e4144b993ca2af794daa53e21f35a", null ],
      [ "rxData", "group__dspi__driver.html#aa58335de5bfa8923228432b62ea9308a", null ],
      [ "state", "group__dspi__driver.html#a06fcd46097cb1779eaa383a6419cd27d", null ],
      [ "totalByteCount", "group__dspi__driver.html#a4ae9e659b40b257243e623c3ded3389d", null ],
      [ "txData", "group__dspi__driver.html#ab56d8f300582ce9d7f4a79729124739d", null ],
      [ "userData", "group__dspi__driver.html#a2e294dd14122c554baa0665072b4ca7a", null ]
    ] ],
    [ "dspi_slave_handle_t", "group__dspi__driver.html#struct__dspi__slave__handle", [
      [ "bitsPerFrame", "group__dspi__driver.html#a8ccf58110b76fd897fd5861ec36ba249", null ],
      [ "callback", "group__dspi__driver.html#a8bc7658408095ef17f84258b570673ac", null ],
      [ "errorCount", "group__dspi__driver.html#a2a11c9c06fe4f8a45030f131e5800ae4", null ],
      [ "isThereExtraByte", "group__dspi__driver.html#af01b42dfc4c4be3e12be53f4721b6e5a", null ],
      [ "remainingReceiveByteCount", "group__dspi__driver.html#afeddb18283b63e45997bdd7cae9a698e", null ],
      [ "remainingSendByteCount", "group__dspi__driver.html#a661e4144b993ca2af794daa53e21f35a", null ],
      [ "rxData", "group__dspi__driver.html#aa58335de5bfa8923228432b62ea9308a", null ],
      [ "state", "group__dspi__driver.html#a06fcd46097cb1779eaa383a6419cd27d", null ],
      [ "totalByteCount", "group__dspi__driver.html#a4ae9e659b40b257243e623c3ded3389d", null ],
      [ "txData", "group__dspi__driver.html#ab56d8f300582ce9d7f4a79729124739d", null ],
      [ "userData", "group__dspi__driver.html#a2e294dd14122c554baa0665072b4ca7a", null ]
    ] ],
    [ "dspi_master_transfer_callback_t", "group__dspi__driver.html#ga67d91a817bd68468037b7886ea710ffa", null ],
    [ "dspi_slave_transfer_callback_t", "group__dspi__driver.html#gaf928cd95fbb7eb5d5f306c9a4d4afce4", null ],
    [ "_dspi_dma_enable", "group__dspi__driver.html#gae3359796dc0680797b1f74b83fc0c0d9", [
      [ "kDSPI_TxDmaEnable", "group__dspi__driver.html#ggae3359796dc0680797b1f74b83fc0c0d9ae772dc49e5a28df00b817f9c6dab0749", null ],
      [ "kDSPI_RxDmaEnable", "group__dspi__driver.html#ggae3359796dc0680797b1f74b83fc0c0d9a15ec9c9897199d53a1b354ccce6d0445", null ]
    ] ],
    [ "_dspi_flags", "group__dspi__driver.html#ga2bfefaf6ba65ba464e764d1c918c904f", [
      [ "kDSPI_TxCompleteFlag", "group__dspi__driver.html#gga2bfefaf6ba65ba464e764d1c918c904faffc8e8711d9083470cddb0db647b75b0", null ],
      [ "kDSPI_EndOfQueueFlag", "group__dspi__driver.html#gga2bfefaf6ba65ba464e764d1c918c904fae91c7a5cc2a90fa051c89f13bbb6d8ed", null ],
      [ "kDSPI_TxFifoUnderflowFlag", "group__dspi__driver.html#gga2bfefaf6ba65ba464e764d1c918c904fae36215137d8ce7cf215349199db877b7", null ],
      [ "kDSPI_TxFifoFillRequestFlag", "group__dspi__driver.html#gga2bfefaf6ba65ba464e764d1c918c904fae9704d53b57758969f8ea5ea6c86f7f0", null ],
      [ "kDSPI_RxFifoOverflowFlag", "group__dspi__driver.html#gga2bfefaf6ba65ba464e764d1c918c904fa30f039adca01f89dbbd02f70dff725ee", null ],
      [ "kDSPI_RxFifoDrainRequestFlag", "group__dspi__driver.html#gga2bfefaf6ba65ba464e764d1c918c904fa092b7f39357ce8cb82ec825e93536605", null ],
      [ "kDSPI_TxAndRxStatusFlag", "group__dspi__driver.html#gga2bfefaf6ba65ba464e764d1c918c904fa58771b3977aef221dab6a67a6739f8d6", null ],
      [ "kDSPI_AllStatusFlag", "group__dspi__driver.html#gga2bfefaf6ba65ba464e764d1c918c904fa4a742818251256d8fc35ab63a6af9c9e", null ]
    ] ],
    [ "_dspi_interrupt_enable", "group__dspi__driver.html#gaeb57298690a2f1a09d94d696c893c4b2", [
      [ "kDSPI_TxCompleteInterruptEnable", "group__dspi__driver.html#ggaeb57298690a2f1a09d94d696c893c4b2ab2b1ba228fd75de23a2de7e56c1ee438", null ],
      [ "kDSPI_EndOfQueueInterruptEnable", "group__dspi__driver.html#ggaeb57298690a2f1a09d94d696c893c4b2a069483b28469fcbfa5890b04cd6439b3", null ],
      [ "kDSPI_TxFifoUnderflowInterruptEnable", "group__dspi__driver.html#ggaeb57298690a2f1a09d94d696c893c4b2aa430e623e0bb240752381eaddda1a973", null ],
      [ "kDSPI_TxFifoFillRequestInterruptEnable", "group__dspi__driver.html#ggaeb57298690a2f1a09d94d696c893c4b2ada57830661d523d12e49892060fde201", null ],
      [ "kDSPI_RxFifoOverflowInterruptEnable", "group__dspi__driver.html#ggaeb57298690a2f1a09d94d696c893c4b2a190746a0aeaa61db32c6c1a7b850d0ee", null ],
      [ "kDSPI_RxFifoDrainRequestInterruptEnable", "group__dspi__driver.html#ggaeb57298690a2f1a09d94d696c893c4b2aa7d99e6ac31bd6c7d835d89f36cec1a6", null ],
      [ "kDSPI_AllInterruptEnable", "group__dspi__driver.html#ggaeb57298690a2f1a09d94d696c893c4b2a530d972d6cd16ab6e929d7ddaaf09b30", null ]
    ] ],
    [ "_dspi_pcs_polarity", "group__dspi__driver.html#gad23a66cefb04826de83504ad485f19a9", [
      [ "kDSPI_Pcs0ActiveLow", "group__dspi__driver.html#ggad23a66cefb04826de83504ad485f19a9ac731b21eefcc16342d2c606a12a00547", null ],
      [ "kDSPI_Pcs1ActiveLow", "group__dspi__driver.html#ggad23a66cefb04826de83504ad485f19a9aa6ee5dca40cbe9bf03623cf986adbadd", null ],
      [ "kDSPI_Pcs2ActiveLow", "group__dspi__driver.html#ggad23a66cefb04826de83504ad485f19a9a6fd76d22cb6c8f943ae397bb91ba68f4", null ],
      [ "kDSPI_Pcs3ActiveLow", "group__dspi__driver.html#ggad23a66cefb04826de83504ad485f19a9a57e33d7e4195864f89db11d2f5e6cc4b", null ],
      [ "kDSPI_Pcs4ActiveLow", "group__dspi__driver.html#ggad23a66cefb04826de83504ad485f19a9a15c201d8e7bd0bab1dd7117b73a111ec", null ],
      [ "kDSPI_Pcs5ActiveLow", "group__dspi__driver.html#ggad23a66cefb04826de83504ad485f19a9a88e1e00a5a7755561358f004a5a1b1d4", null ],
      [ "kDSPI_PcsAllActiveLow", "group__dspi__driver.html#ggad23a66cefb04826de83504ad485f19a9adb2bef5058b4bf00533cc89f1928e2d1", null ]
    ] ],
    [ "_dspi_status", "group__dspi__driver.html#ga06b41ab984bc03e6f1eb07988edcb3ea", [
      [ "kStatus_DSPI_Busy", "group__dspi__driver.html#gga06b41ab984bc03e6f1eb07988edcb3eaad5ecc8346da4119b8609c6bcb4c57e40", null ],
      [ "kStatus_DSPI_Error", "group__dspi__driver.html#gga06b41ab984bc03e6f1eb07988edcb3eaaaae2ba17a6a622142816b0ffec7b9f7a", null ],
      [ "kStatus_DSPI_Idle", "group__dspi__driver.html#gga06b41ab984bc03e6f1eb07988edcb3eaa638dc0d050e7660225a46cc7cd6e38c7", null ],
      [ "kStatus_DSPI_OutOfRange", "group__dspi__driver.html#gga06b41ab984bc03e6f1eb07988edcb3eaac1713712f0410e28da008d714734a6bd", null ]
    ] ],
    [ "_dspi_transfer_config_flag_for_master", "group__dspi__driver.html#gac74dfe19c844271a393314a4fd13792f", [
      [ "kDSPI_MasterCtar0", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792faf7ddf42278af30a1b81f10c4058ecddd", null ],
      [ "kDSPI_MasterCtar1", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa57508605f5d5fb0a2fb7eddfcdb89f12", null ],
      [ "kDSPI_MasterCtar2", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa6cf50df8fd75f5be1347efcaec8a68f4", null ],
      [ "kDSPI_MasterCtar3", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa70471fdf900dba881f4e742d303d307c", null ],
      [ "kDSPI_MasterCtar4", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792faad989e96bfed1f2fbb0fcc3adb99d04b", null ],
      [ "kDSPI_MasterCtar5", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa5c3dbe0ddb8e9f3f67496592ef3ec902", null ],
      [ "kDSPI_MasterCtar6", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa5e898da1cd4e093f048f947bc751b7fa", null ],
      [ "kDSPI_MasterCtar7", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa90cf553b9933d1e3d692469e0fa5ddc3", null ],
      [ "kDSPI_MasterPcs0", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fad51bd34d51062d900b07801e0fd193cc", null ],
      [ "kDSPI_MasterPcs1", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fad07c95fafd30869cb6110d4ea3ed7ca1", null ],
      [ "kDSPI_MasterPcs2", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa116fef8c0a72727a80e72e1d1d0d0ffc", null ],
      [ "kDSPI_MasterPcs3", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa2266cc2ddbf05da3164fa6ad680facd9", null ],
      [ "kDSPI_MasterPcs4", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa3b32f4a57a5aaaaf0064d7ec1373a154", null ],
      [ "kDSPI_MasterPcs5", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa8047faff72926a57c0659f4147787353", null ],
      [ "kDSPI_MasterPcsContinuous", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa8309b1b52bbaa930bbcc3e2407f1a6f5", null ],
      [ "kDSPI_MasterActiveAfterTransfer", "group__dspi__driver.html#ggac74dfe19c844271a393314a4fd13792fa458df11cc493759474f31873cfa8d4c1", null ]
    ] ],
    [ "_dspi_transfer_config_flag_for_slave", "group__dspi__driver.html#ga5070a73633ee72428adda72058f7fb5f", [
      [ "kDSPI_SlaveCtar0", "group__dspi__driver.html#gga5070a73633ee72428adda72058f7fb5fa6e63c217f9b392f78fb96ee039c991c8", null ]
    ] ],
    [ "_dspi_transfer_state", "group__dspi__driver.html#ga97c65523863f89cddbf06691c678a7f9", [
      [ "kDSPI_Idle", "group__dspi__driver.html#gga97c65523863f89cddbf06691c678a7f9ae739fb0dabff3a7cb72c39eef943a373", null ],
      [ "kDSPI_Busy", "group__dspi__driver.html#gga97c65523863f89cddbf06691c678a7f9a4b636d65ab83d136e81ed31e30de4429", null ],
      [ "kDSPI_Error", "group__dspi__driver.html#gga97c65523863f89cddbf06691c678a7f9a6d94f11a50f542371683efe9ea22efb9", null ]
    ] ],
    [ "dspi_clock_phase_t", "group__dspi__driver.html#ga4269ec144334dd60666a92e6fd2c1476", [
      [ "kDSPI_ClockPhaseFirstEdge", "group__dspi__driver.html#gga4269ec144334dd60666a92e6fd2c1476a996e921abbf325ee9978a42681aee0d5", null ],
      [ "kDSPI_ClockPhaseSecondEdge", "group__dspi__driver.html#gga4269ec144334dd60666a92e6fd2c1476a43ee643e847b3118e38da0a9811d97f9", null ]
    ] ],
    [ "dspi_clock_polarity_t", "group__dspi__driver.html#ga1e0a9074742794ef89f597d220296651", [
      [ "kDSPI_ClockPolarityActiveHigh", "group__dspi__driver.html#gga1e0a9074742794ef89f597d220296651ab5279f36f0c6b1617aa937824806d71d", null ],
      [ "kDSPI_ClockPolarityActiveLow", "group__dspi__driver.html#gga1e0a9074742794ef89f597d220296651abcde58b8834e5cd1181b8b98aa4a10ef", null ]
    ] ],
    [ "dspi_ctar_selection_t", "group__dspi__driver.html#ga992d5562af4cf4c45371feb8c5c1a1bf", [
      [ "kDSPI_Ctar0", "group__dspi__driver.html#gga992d5562af4cf4c45371feb8c5c1a1bfadb2a4c8c9b722c6a1b8cbb03b17a6519", null ],
      [ "kDSPI_Ctar1", "group__dspi__driver.html#gga992d5562af4cf4c45371feb8c5c1a1bfad6db3f5779fd74fdfa9bda2375573227", null ],
      [ "kDSPI_Ctar2", "group__dspi__driver.html#gga992d5562af4cf4c45371feb8c5c1a1bfa406d09f42f5e009617a40f4c30cc10d9", null ],
      [ "kDSPI_Ctar3", "group__dspi__driver.html#gga992d5562af4cf4c45371feb8c5c1a1bfaf1df973bc8d89efbfb8d7bff51af0265", null ],
      [ "kDSPI_Ctar4", "group__dspi__driver.html#gga992d5562af4cf4c45371feb8c5c1a1bfa13960000166ae1cc18b19f5c4c9405ff", null ],
      [ "kDSPI_Ctar5", "group__dspi__driver.html#gga992d5562af4cf4c45371feb8c5c1a1bfad0b231829a94051ce913cd367135c1f2", null ],
      [ "kDSPI_Ctar6", "group__dspi__driver.html#gga992d5562af4cf4c45371feb8c5c1a1bfaa7bb6aaabeb65811e58af0460c38e373", null ],
      [ "kDSPI_Ctar7", "group__dspi__driver.html#gga992d5562af4cf4c45371feb8c5c1a1bfa6ae1a9c5243a507f36c3db1ef14c216e", null ]
    ] ],
    [ "dspi_delay_type_t", "group__dspi__driver.html#ga1ca2fbee37b3cb046c075a7e765d64ed", [
      [ "kDSPI_PcsToSck", "group__dspi__driver.html#gga1ca2fbee37b3cb046c075a7e765d64eda71185ae0d4d9dd61acbc69bce93f33f5", null ],
      [ "kDSPI_LastSckToPcs", "group__dspi__driver.html#gga1ca2fbee37b3cb046c075a7e765d64edaa2ce775b9575a3870ce82b8444b9d56c", null ],
      [ "kDSPI_BetweenTransfer", "group__dspi__driver.html#gga1ca2fbee37b3cb046c075a7e765d64eda83ed3f05b8a61f94c0da066c1ded7a1e", null ]
    ] ],
    [ "dspi_master_sample_point_t", "group__dspi__driver.html#gae783895e2917abe07adbe27a253510a2", [
      [ "kDSPI_SckToSin0Clock", "group__dspi__driver.html#ggae783895e2917abe07adbe27a253510a2abbcf84bafbd94a63a9600647162b8d86", null ],
      [ "kDSPI_SckToSin1Clock", "group__dspi__driver.html#ggae783895e2917abe07adbe27a253510a2a61e5f5d7122c849c737513ae7c5c4c50", null ],
      [ "kDSPI_SckToSin2Clock", "group__dspi__driver.html#ggae783895e2917abe07adbe27a253510a2a305d68c9446ca0866da7a2ace743ae4d", null ]
    ] ],
    [ "dspi_master_slave_mode_t", "group__dspi__driver.html#gad7f974015f32db057dafada8b95641aa", [
      [ "kDSPI_Master", "group__dspi__driver.html#ggad7f974015f32db057dafada8b95641aaa8330c6ad827da3c783df5805244fa7d9", null ],
      [ "kDSPI_Slave", "group__dspi__driver.html#ggad7f974015f32db057dafada8b95641aaa2e075745386fd71bee2535606f29dd87", null ]
    ] ],
    [ "dspi_pcs_polarity_config_t", "group__dspi__driver.html#gab466e73cb54b2c023459d43918c4197d", [
      [ "kDSPI_PcsActiveHigh", "group__dspi__driver.html#ggab466e73cb54b2c023459d43918c4197da79a6807edd30a1230477ab26068060fd", null ],
      [ "kDSPI_PcsActiveLow", "group__dspi__driver.html#ggab466e73cb54b2c023459d43918c4197daa678a5937bbb9975e3c014592c3d542c", null ]
    ] ],
    [ "dspi_shift_direction_t", "group__dspi__driver.html#ga06fad8ae17b680f6dddfd798c9d3b30d", [
      [ "kDSPI_MsbFirst", "group__dspi__driver.html#gga06fad8ae17b680f6dddfd798c9d3b30da8885a916a15d0b97ffd0f28d81242f6f", null ],
      [ "kDSPI_LsbFirst", "group__dspi__driver.html#gga06fad8ae17b680f6dddfd798c9d3b30da76701314fa7dbd70e4011feb326b9050", null ]
    ] ],
    [ "dspi_which_pcs_t", "group__dspi__driver.html#ga36d77cff6cfa202e0ff3a05ab4c2a632", [
      [ "kDSPI_Pcs0", "group__dspi__driver.html#gga36d77cff6cfa202e0ff3a05ab4c2a632a5c6297be9586ee874fa1a84a16d810b7", null ],
      [ "kDSPI_Pcs1", "group__dspi__driver.html#gga36d77cff6cfa202e0ff3a05ab4c2a632a62d3c43292cebeed478a36bff2cd033a", null ],
      [ "kDSPI_Pcs2", "group__dspi__driver.html#gga36d77cff6cfa202e0ff3a05ab4c2a632a625c90d5151e8458be6f89ace68f2fe2", null ],
      [ "kDSPI_Pcs3", "group__dspi__driver.html#gga36d77cff6cfa202e0ff3a05ab4c2a632a7fae848c0f775a86562b90ecfd171cc8", null ],
      [ "kDSPI_Pcs4", "group__dspi__driver.html#gga36d77cff6cfa202e0ff3a05ab4c2a632a0fd968cdbfd2e088987e309f49cb20f2", null ],
      [ "kDSPI_Pcs5", "group__dspi__driver.html#gga36d77cff6cfa202e0ff3a05ab4c2a632a67653d39cbd675c9141bb014d4576a0b", null ]
    ] ],
    [ "DSPI_ClearStatusFlags", "group__dspi__driver.html#ga11454768ad4c96b65b298cccf1f0401c", null ],
    [ "DSPI_Deinit", "group__dspi__driver.html#gaa669bb8f6438b1d4f7ec38ba180653fa", null ],
    [ "DSPI_DisableDMA", "group__dspi__driver.html#ga543b12952cb5ac404ebbdaa572628c8e", null ],
    [ "DSPI_DisableInterrupts", "group__dspi__driver.html#gabf5c4ec1216387b8c476853e45a9bfeb", null ],
    [ "DSPI_Enable", "group__dspi__driver.html#ga38a2ee1ed351246ebbdc4b242b835164", null ],
    [ "DSPI_EnableDMA", "group__dspi__driver.html#ga313d41fd54ca75781bb7596b319d4849", null ],
    [ "DSPI_EnableInterrupts", "group__dspi__driver.html#ga9b9e4c8ae54ea108952c80940e11b3a8", null ],
    [ "DSPI_FlushFifo", "group__dspi__driver.html#ga3cbb532b5bd6981f5cc0115f49a9ee9a", null ],
    [ "DSPI_GetDefaultDataCommandConfig", "group__dspi__driver.html#gad9f3df616e7284696af57cce8f49899e", null ],
    [ "DSPI_GetRxRegisterAddress", "group__dspi__driver.html#ga0d2bcb0a744852ab2701466a7fd974f6", null ],
    [ "DSPI_GetStatusFlags", "group__dspi__driver.html#ga11005216bf792c91894d9e670b0323f8", null ],
    [ "DSPI_IsMaster", "group__dspi__driver.html#gae606c91960692b493d17d067c38d67b3", null ],
    [ "DSPI_MasterGetDefaultConfig", "group__dspi__driver.html#ga0061c90bc787dc1faffde79cb256e8a4", null ],
    [ "DSPI_MasterGetFormattedCommand", "group__dspi__driver.html#ga4068b27da40c419a700badf2070fc5e4", null ],
    [ "DSPI_MasterGetTxRegisterAddress", "group__dspi__driver.html#gad3e8a8107cfda29dbae45fc5166d63f3", null ],
    [ "DSPI_MasterInit", "group__dspi__driver.html#gaadf23f732f4c1b61d6634bd17b1a36d7", null ],
    [ "DSPI_MasterSetBaudRate", "group__dspi__driver.html#gac76cf793dd837dd0b502770913058592", null ],
    [ "DSPI_MasterSetDelayScaler", "group__dspi__driver.html#ga56d5b87114e56507c0ec2d631ffefaa2", null ],
    [ "DSPI_MasterSetDelayTimes", "group__dspi__driver.html#gac60f64fd410404ebab553ee878b464c2", null ],
    [ "DSPI_MasterTransferAbort", "group__dspi__driver.html#ga80633e998c10cb83685d6c64ecd33a55", null ],
    [ "DSPI_MasterTransferBlocking", "group__dspi__driver.html#gab2d0aa3acb2acc3cc5413314d758628b", null ],
    [ "DSPI_MasterTransferCreateHandle", "group__dspi__driver.html#ga63e04b92d99d795cf84df62379765a91", null ],
    [ "DSPI_MasterTransferGetCount", "group__dspi__driver.html#gadaf98a7213c03f10d5820d363e827a73", null ],
    [ "DSPI_MasterTransferHandleIRQ", "group__dspi__driver.html#ga195eed1bfdc0d21e7adb76a5d6d247dc", null ],
    [ "DSPI_MasterTransferNonBlocking", "group__dspi__driver.html#gad3dc7b85b448ce6e16e227d7bf3769d6", null ],
    [ "DSPI_MasterWriteCommandDataBlocking", "group__dspi__driver.html#ga0718581088422b572cb4494f26aad1f9", null ],
    [ "DSPI_MasterWriteData", "group__dspi__driver.html#gabe0d615b273c4cb0eaf26d9679b73ad6", null ],
    [ "DSPI_MasterWriteDataBlocking", "group__dspi__driver.html#ga70a0f7d7fe2fbce7993bbcc8c427b2b0", null ],
    [ "DSPI_ReadData", "group__dspi__driver.html#gaee93673062a6fb105dcf1e0541dd8b52", null ],
    [ "DSPI_SetAllPcsPolarity", "group__dspi__driver.html#ga1c42d5efc75982041f4a66f4f1fc71a4", null ],
    [ "DSPI_SetFifoEnable", "group__dspi__driver.html#gad9112153c575eeeb6af747d9e6396514", null ],
    [ "DSPI_SetMasterSlaveMode", "group__dspi__driver.html#gac3e11f3876e81d7636a77fb268c2365a", null ],
    [ "DSPI_SlaveGetDefaultConfig", "group__dspi__driver.html#gad85a8d4e7bd2747103691a63ef9a67e1", null ],
    [ "DSPI_SlaveGetTxRegisterAddress", "group__dspi__driver.html#ga8912754715dfadde5473a419f7b8ff93", null ],
    [ "DSPI_SlaveInit", "group__dspi__driver.html#gacf6cecb6b73f02eaa448634a8d705851", null ],
    [ "DSPI_SlaveTransferAbort", "group__dspi__driver.html#ga7e1be1f74fd8d372ce1af52c960d1361", null ],
    [ "DSPI_SlaveTransferCreateHandle", "group__dspi__driver.html#gadc23691aa2c06ae9076a5f0b16f33a8c", null ],
    [ "DSPI_SlaveTransferGetCount", "group__dspi__driver.html#ga4134bb536420951e8ecbe8edb987d199", null ],
    [ "DSPI_SlaveTransferHandleIRQ", "group__dspi__driver.html#gade8288c503cc6c7af542cdc86947ecd3", null ],
    [ "DSPI_SlaveTransferNonBlocking", "group__dspi__driver.html#ga81f85324750f75b8e7248846c88d99e7", null ],
    [ "DSPI_SlaveWriteData", "group__dspi__driver.html#ga952c2bfcb7e3ac7d3608ec16add273dc", null ],
    [ "DSPI_SlaveWriteDataBlocking", "group__dspi__driver.html#gad7a98ccdb5dcd3ea9c282893b79cee79", null ],
    [ "DSPI_StartTransfer", "group__dspi__driver.html#gac3fb40ea05b407f5b335c0a47330e3a8", null ],
    [ "DSPI_StopTransfer", "group__dspi__driver.html#ga09021ebd27d4ccf5d85398b5bbf12045", null ]
];