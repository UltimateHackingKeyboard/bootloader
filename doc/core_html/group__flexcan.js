var group__flexcan =
[
    [ "FlexCAN driver", "group__flexcan__driver.html", null ],
    [ "flexcan_frame_t", "group__flexcan.html#structflexcan__frame__t", null ],
    [ "flexcan_frame_t.__unnamed__", "group__flexcan.html#structflexcan__frame__t_8____unnamed____", [
      [ "format", "group__flexcan.html#a1ddcb92ade31c8fbd370001f9b29a7d9", null ],
      [ "idhit", "group__flexcan.html#acbd6011a02e001c09ec353b6b09252ea", null ],
      [ "length", "group__flexcan.html#a2fa47f7c65fec19cc163b195725e3844", null ],
      [ "reserve1", "group__flexcan.html#aff18dd8670600ce99a023f57c80fdfca", null ],
      [ "timestamp", "group__flexcan.html#ad7e6d55ba379a13d08c25d15faf2a23b", null ],
      [ "type", "group__flexcan.html#a599dcce2998a6b40b1e38e8c6006cb0a", null ]
    ] ],
    [ "flexcan_frame_t.__unnamed__.__unnamed__", "group__flexcan.html#structflexcan__frame__t_8____unnamed_____8____unnamed____", [
      [ "dataWord0", "group__flexcan.html#a27acadd7080ac39ef5f00fc14c2dbb90", null ],
      [ "dataWord1", "group__flexcan.html#ace515169bbd919201e6599352ad96d62", null ]
    ] ],
    [ "flexcan_config_t", "group__flexcan.html#structflexcan__config__t", [
      [ "baudRate", "group__flexcan.html#ab38a80feace530cdca66134f6e3801aa", null ],
      [ "clkSrc", "group__flexcan.html#a7d85a13ba707133aa5461e0f1ab92447", null ],
      [ "enableDoze", "group__flexcan.html#adc33c54dc06ce1822fe921591e5b4d8a", null ],
      [ "enableIndividMask", "group__flexcan.html#aff4f0a43027d81d83a6c3ffc92f240e5", null ],
      [ "enableLoopBack", "group__flexcan.html#a6ffda5d2889d11a222d37eafbf8f116a", null ],
      [ "enableSelfWakeup", "group__flexcan.html#a83eb235e89e7ce5f1a5b498582768cb8", null ],
      [ "maxMbNum", "group__flexcan.html#aaada4541e434f55fc2e4c072c77bb7ea", null ]
    ] ],
    [ "flexcan_timing_config_t", "group__flexcan.html#structflexcan__timing__config__t", [
      [ "phaseSeg1", "group__flexcan.html#a8bc08392192fd5564b6ada173a40a2ad", null ],
      [ "phaseSeg2", "group__flexcan.html#a03741a4fda471c631d7711bd119a2afb", null ],
      [ "preDivider", "group__flexcan.html#a9d416dccc631d569824d840325650d7f", null ],
      [ "propSeg", "group__flexcan.html#adfc8ac7951cc527173d9251ca0575bff", null ],
      [ "rJumpwidth", "group__flexcan.html#a926069e4b4113a7b5954176bde3992b3", null ]
    ] ],
    [ "flexcan_rx_mb_config_t", "group__flexcan.html#structflexcan__rx__mb__config__t", [
      [ "format", "group__flexcan.html#a4ee6021c029e3cf49c941dfb9700d02c", null ],
      [ "id", "group__flexcan.html#abaabdc509cdaba7df9f56c6c76f3ae19", null ],
      [ "type", "group__flexcan.html#a870d6ce64781a7b339e47962be8652a2", null ]
    ] ],
    [ "flexcan_rx_fifo_config_t", "group__flexcan.html#structflexcan__rx__fifo__config__t", [
      [ "idFilterNum", "group__flexcan.html#a11214c7a10ff8981572e42e9fcf3f23e", null ],
      [ "idFilterTable", "group__flexcan.html#a02786d9ef095ce8bc774e9c5fb142f13", null ],
      [ "idFilterType", "group__flexcan.html#a1e1b7157f4852f7dabfb04d483bfb1f7", null ],
      [ "priority", "group__flexcan.html#a6b845b9d952d8f5cc1f7869f20fa4e48", null ]
    ] ],
    [ "flexcan_mb_transfer_t", "group__flexcan.html#structflexcan__mb__transfer__t", [
      [ "frame", "group__flexcan.html#aa8dd8f56bc5418920fe9206c19116f26", null ],
      [ "mbIdx", "group__flexcan.html#acc8869dbbe7255ac7f14930f5054d0ac", null ]
    ] ],
    [ "flexcan_fifo_transfer_t", "group__flexcan.html#structflexcan__fifo__transfer__t", [
      [ "frame", "group__flexcan.html#aa8dd8f56bc5418920fe9206c19116f26", null ]
    ] ],
    [ "flexcan_handle_t", "group__flexcan.html#struct__flexcan__handle", [
      [ "callback", "group__flexcan.html#a5f6d85e94314b5532279b9e0e98c7544", null ],
      [ "mbFrameBuf", "group__flexcan.html#a95398f3bf8821c0408b7b6ed84f9f05f", null ],
      [ "mbState", "group__flexcan.html#a1afd9623751b137c2744f8036a168630", null ],
      [ "rxFifoFrameBuf", "group__flexcan.html#a7591fd350df65f339ad7daf3bb8a7ca1", null ],
      [ "rxFifoState", "group__flexcan.html#a276b0b42bf30854ba142d9959108ddae", null ],
      [ "userData", "group__flexcan.html#a2e294dd14122c554baa0665072b4ca7a", null ]
    ] ],
    [ "flexcan_transfer_callback_t", "group__flexcan.html#ga4df171e52fae160f2e48257b864ce2e9", null ],
    [ "_flexcan_error_flags", "group__flexcan.html#gae49fa3b7177a77bb6441a251d7d1c04b", [
      [ "kFLEXCAN_StuffingError", "group__flexcan.html#ggae49fa3b7177a77bb6441a251d7d1c04baf29ecd380ebf9e3c2ba942d1b59afd20", null ],
      [ "kFLEXCAN_FormError", "group__flexcan.html#ggae49fa3b7177a77bb6441a251d7d1c04baa2a20d23736022638dff3fa399a28228", null ],
      [ "kFLEXCAN_CrcError", "group__flexcan.html#ggae49fa3b7177a77bb6441a251d7d1c04bab668e1723ddbd49091b8fd40ff58d0de", null ],
      [ "kFLEXCAN_AckError", "group__flexcan.html#ggae49fa3b7177a77bb6441a251d7d1c04ba2e89a0bda4c49a0b3b186c4f53b66a21", null ],
      [ "kFLEXCAN_Bit0Error", "group__flexcan.html#ggae49fa3b7177a77bb6441a251d7d1c04bafbb466f580b3a3b5fac17856f018ada8", null ],
      [ "kFLEXCAN_Bit1Error", "group__flexcan.html#ggae49fa3b7177a77bb6441a251d7d1c04bac507066e62503970fbc6efd5d573f055", null ]
    ] ],
    [ "_flexcan_flags", "group__flexcan.html#gafcf014e17652c04821de5596f5c4f247", [
      [ "kFLEXCAN_SynchFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247a5200e04525a33c3d17abb0902423fd65", null ],
      [ "kFLEXCAN_TxWarningIntFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247aeb17959193db08c88ebe1acec32bf5a9", null ],
      [ "kFLEXCAN_RxWarningIntFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247a1f2987e32d2889a23140b20e72405973", null ],
      [ "kFLEXCAN_TxErrorWarningFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247ad2f12389f5b32bbb7d84c9718d4e2e8b", null ],
      [ "kFLEXCAN_RxErrorWarningFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247acc85a7f4c13805e8a0ec9e5cf0f6b7e2", null ],
      [ "kFLEXCAN_IdleFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247a763c9217bed2fa7c5c1f12e2459f61f0", null ],
      [ "kFLEXCAN_FaultConfinementFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247a3ca2089ad4230485f0351c718a962d2e", null ],
      [ "kFLEXCAN_TransmittingFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247a03ff01b35c352d48288a60ba686bb94b", null ],
      [ "kFLEXCAN_ReceivingFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247a26c976e3327f4c08e60eb4a980ecb44e", null ],
      [ "kFLEXCAN_BusOffIntFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247ab3db871ba55aea71f9fb6a9eda3d4480", null ],
      [ "kFLEXCAN_ErrorIntFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247afa70d0ee5c86b648e7da37d16a1e9cfe", null ],
      [ "kFLEXCAN_WakeUpIntFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247abb5e5668b2be3d78e30c7f666b402816", null ],
      [ "kFLEXCAN_ErrorFlag", "group__flexcan.html#ggafcf014e17652c04821de5596f5c4f247a9dec4cce221940055dc269cb06e9e0f1", null ]
    ] ],
    [ "_flexcan_interrupt_enable", "group__flexcan.html#ga339a68a513c218f67756e2a04985428e", [
      [ "kFLEXCAN_BusOffInterruptEnable", "group__flexcan.html#gga339a68a513c218f67756e2a04985428eac07643ed5772e0666315c8cf38d1912a", null ],
      [ "kFLEXCAN_ErrorInterruptEnable", "group__flexcan.html#gga339a68a513c218f67756e2a04985428ea1943b187ec63f3a34660d5c48ada5cf6", null ],
      [ "kFLEXCAN_RxWarningInterruptEnable", "group__flexcan.html#gga339a68a513c218f67756e2a04985428ea776a58431fab2cca17e5b859bbd25d8e", null ],
      [ "kFLEXCAN_TxWarningInterruptEnable", "group__flexcan.html#gga339a68a513c218f67756e2a04985428eaa91344d65339ed9f0b2801f772c8cf90", null ],
      [ "kFLEXCAN_WakeUpInterruptEnable", "group__flexcan.html#gga339a68a513c218f67756e2a04985428eaab59629e2da9dc184add56eebe85bf5f", null ]
    ] ],
    [ "_flexcan_rx_fifo_flags", "group__flexcan.html#gacbdc64ada450fa6e8428aca3bcc7d8a9", [
      [ "kFLEXCAN_RxFifoOverflowFlag", "group__flexcan.html#ggacbdc64ada450fa6e8428aca3bcc7d8a9aaea98e3313f0b74f0485fe39425fdb79", null ],
      [ "kFLEXCAN_RxFifoWarningFlag", "group__flexcan.html#ggacbdc64ada450fa6e8428aca3bcc7d8a9aa1faa3742f1c027714f92db80310e33f", null ],
      [ "kFLEXCAN_RxFifoFrameAvlFlag", "group__flexcan.html#ggacbdc64ada450fa6e8428aca3bcc7d8a9a0d78a5c058c0908b5a0f43997046965f", null ]
    ] ],
    [ "_flexcan_status", "group__flexcan.html#ga73b6375147061a131ec4d3959f2b950b", [
      [ "kStatus_FLEXCAN_TxBusy", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba0080617424605a0a0a95e3333f24b3e4", null ],
      [ "kStatus_FLEXCAN_TxIdle", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba91fc36f54041f079bd0cbec9dedac200", null ],
      [ "kStatus_FLEXCAN_TxSwitchToRx", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba1faddda6dd8b232ad54604365e2d605d", null ],
      [ "kStatus_FLEXCAN_RxBusy", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba5b713aab29b9accd29aa58d8dc4447e7", null ],
      [ "kStatus_FLEXCAN_RxIdle", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950bae2b4dcba97c6f468046168046135af67", null ],
      [ "kStatus_FLEXCAN_RxOverflow", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba8e2d4031323b8747c5d74c6275e3b9f1", null ],
      [ "kStatus_FLEXCAN_RxFifoBusy", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba74adab69bc91962510c1cc1faa96220d", null ],
      [ "kStatus_FLEXCAN_RxFifoIdle", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba6b1ace2daae9aa209f6c57e8e1dae2f5", null ],
      [ "kStatus_FLEXCAN_RxFifoOverflow", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba257602d134fb16ca03908ba7ef9c5e0f", null ],
      [ "kStatus_FLEXCAN_RxFifoWarning", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba49de45608b1bef73b58f59b5aac6e459", null ],
      [ "kStatus_FLEXCAN_ErrorStatus", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba08579ac6bdc65a85046b33cd0d5d636a", null ],
      [ "kStatus_FLEXCAN_UnHandled", "group__flexcan.html#gga73b6375147061a131ec4d3959f2b950ba853b75a2a57e9d380ee85ab69da946cc", null ]
    ] ],
    [ "flexcan_clock_source_t", "group__flexcan.html#gaa0b3ac1e2e7416950b82014d2a2b40ee", [
      [ "kFLEXCAN_ClkSrcOsc", "group__flexcan.html#ggaa0b3ac1e2e7416950b82014d2a2b40eead9cb66012e8d50e9ee3e154a36c1cff1", null ],
      [ "kFLEXCAN_ClkSrcPeri", "group__flexcan.html#ggaa0b3ac1e2e7416950b82014d2a2b40eea962bcf8760c6a23e054980b1d0c5a922", null ]
    ] ],
    [ "flexcan_frame_format_t", "group__flexcan.html#ga89e76f77a571693c1adeec47796c97df", [
      [ "kFLEXCAN_FrameFormatStandard", "group__flexcan.html#gga89e76f77a571693c1adeec47796c97dfa82e576bc13cb647a948eed52564d109b", null ],
      [ "kFLEXCAN_FrameFormatExtend", "group__flexcan.html#gga89e76f77a571693c1adeec47796c97dfa2acf770880d063c0522a5cc762ab2638", null ]
    ] ],
    [ "flexcan_frame_type_t", "group__flexcan.html#gacec96742e2b0b51a5bf3246bfc57a455", [
      [ "kFLEXCAN_FrameTypeData", "group__flexcan.html#ggacec96742e2b0b51a5bf3246bfc57a455a650a94706925910caaaef592a99f77b3", null ],
      [ "kFLEXCAN_FrameTypeRemote", "group__flexcan.html#ggacec96742e2b0b51a5bf3246bfc57a455ab8f92265dc2dadff64259080c78fa35e", null ]
    ] ],
    [ "flexcan_rx_fifo_filter_type_t", "group__flexcan.html#ga1b8c38cce54aff2f24b6cd45da80f353", [
      [ "kFLEXCAN_RxFifoFilterTypeA", "group__flexcan.html#gga1b8c38cce54aff2f24b6cd45da80f353a1791608b19ef6a27483f55fee614f764", null ],
      [ "kFLEXCAN_RxFifoFilterTypeB", "group__flexcan.html#gga1b8c38cce54aff2f24b6cd45da80f353a0989630ff89813979a12fd56e772073c", null ],
      [ "kFLEXCAN_RxFifoFilterTypeC", "group__flexcan.html#gga1b8c38cce54aff2f24b6cd45da80f353ae4f020795b2ffb38eafb9a3648270a19", null ],
      [ "kFLEXCAN_RxFifoFilterTypeD", "group__flexcan.html#gga1b8c38cce54aff2f24b6cd45da80f353a6b221467793b4268bf84cd475b92780d", null ]
    ] ],
    [ "flexcan_rx_fifo_priority_t", "group__flexcan.html#ga5d139af23e8c1094b39d1cf26d85271b", [
      [ "kFLEXCAN_RxFifoPrioLow", "group__flexcan.html#gga5d139af23e8c1094b39d1cf26d85271babc83bc44026aa8c9eef2a4b259e05ecd", null ],
      [ "kFLEXCAN_RxFifoPrioHigh", "group__flexcan.html#gga5d139af23e8c1094b39d1cf26d85271bac2b9710c6248536f992bdd832d05f8cf", null ]
    ] ],
    [ "FLEXCAN_ClearMbStatusFlags", "group__flexcan.html#ga800056b1b1ee4748d086329535e78274", null ],
    [ "FLEXCAN_ClearStatusFlags", "group__flexcan.html#gace1fd2bc62b4f7c71d1fce292adf3b3a", null ],
    [ "FLEXCAN_Deinit", "group__flexcan.html#ga0629aa8318a3e515dfb168004e0ce656", null ],
    [ "FLEXCAN_DisableInterrupts", "group__flexcan.html#gad6e220545b129d120fac805e8f9d82ab", null ],
    [ "FLEXCAN_DisableMbInterrupts", "group__flexcan.html#ga78548c5ae0c0a4b2148712ef6aa770db", null ],
    [ "FLEXCAN_Enable", "group__flexcan.html#ga20f79302d5fad90306a26b667f58fe4d", null ],
    [ "FLEXCAN_EnableInterrupts", "group__flexcan.html#ga406e9c07a20ed89504c5716f02efb957", null ],
    [ "FLEXCAN_EnableMbInterrupts", "group__flexcan.html#ga67840cca27caffb0247dd03c5c07d6de", null ],
    [ "FLEXCAN_EnableRxFifoDMA", "group__flexcan.html#gab3bf9b8856103be2045e5d5050b236d6", null ],
    [ "FlEXCAN_GetBusErrCount", "group__flexcan.html#ga6b042a7d31e057b96e16954d7342c9b4", null ],
    [ "FLEXCAN_GetDefaultConfig", "group__flexcan.html#ga4eafdb971a92f517c69a80c15a216342", null ],
    [ "FLEXCAN_GetMbStatusFlags", "group__flexcan.html#gab6ed94b8a36d174fb30d3256e3b2d975", null ],
    [ "FLEXCAN_GetRxFifoHeadAddr", "group__flexcan.html#ga5391b69b149d1e640e52807eb96a08ef", null ],
    [ "FLEXCAN_GetStatusFlags", "group__flexcan.html#ga46217b1ae979c927ae59b98fbbb181e3", null ],
    [ "FLEXCAN_Init", "group__flexcan.html#ga8d7ebf086fb294130fa30a0f75a5f340", null ],
    [ "FlEXCAN_ReadRxFifo", "group__flexcan.html#ga0f74840527f5e882c72746315bc06576", null ],
    [ "FLEXCAN_ReadRxMb", "group__flexcan.html#ga93600de1691b5e6d8cc01e06efee7b68", null ],
    [ "FlEXCAN_SetRxFifoConfig", "group__flexcan.html#ga40140a86bc8481442286a61aa668d508", null ],
    [ "FlEXCAN_SetRxFifoGlobalMask", "group__flexcan.html#ga6916d2efb57c72bc39450728d63eda2e", null ],
    [ "FlEXCAN_SetRxIndividualMask", "group__flexcan.html#ga4e097e264335f27dc55f20c4eb836a94", null ],
    [ "FLEXCAN_SetRxMbConfig", "group__flexcan.html#gaf335daf0156fab50571e55d2898bccb2", null ],
    [ "FlEXCAN_SetRxMbGlobalMask", "group__flexcan.html#ga188e40d55493a20e7e11215d23369f94", null ],
    [ "FLEXCAN_SetTimingConfig", "group__flexcan.html#ga481abb41cf9d87c7b4a901dd61e34f82", null ],
    [ "FLEXCAN_SetTxMbConfig", "group__flexcan.html#gadbf35cc05ed0d9a73eda5ac4fbb30ff0", null ],
    [ "FLEXCAN_TransferAbortReceive", "group__flexcan.html#ga96d909308b07c826b8123b45bf46e2e8", null ],
    [ "FLEXCAN_TransferAbortReceiveFifo", "group__flexcan.html#ga9ff071840674c2b3f2e1667e5d0400ac", null ],
    [ "FLEXCAN_TransferAbortSend", "group__flexcan.html#gab1bb142ae44f89723de55aed6879d311", null ],
    [ "FLEXCAN_TransferCreateHandle", "group__flexcan.html#gaca661014e03aa709a753a3c499ecba19", null ],
    [ "FLEXCAN_TransferHandleIRQ", "group__flexcan.html#ga929cb775ee9a363295feef9cb06c2425", null ],
    [ "FlEXCAN_TransferReceiveBlocking", "group__flexcan.html#gafaa8ec3bde747737139a4cfc64c64c61", null ],
    [ "FlEXCAN_TransferReceiveFifoBlocking", "group__flexcan.html#ga59891932ccc6001fa5a67b0b5a592367", null ],
    [ "FLEXCAN_TransferReceiveFifoNonBlocking", "group__flexcan.html#gaf47e1a71184fa3079d02a81e2def72cd", null ],
    [ "FLEXCAN_TransferReceiveNonBlocking", "group__flexcan.html#ga8f41d066f0898128a09ef2218eee6618", null ],
    [ "FlEXCAN_TransferSendBlocking", "group__flexcan.html#gac360f0cee2cf46a682ae1fc2d63958d5", null ],
    [ "FLEXCAN_TransferSendNonBlocking", "group__flexcan.html#ga8497b4572e60df692d193e2329993e5f", null ],
    [ "FLEXCAN_WriteTxMb", "group__flexcan.html#ga9ee9d599069a88a50cb7c7a894c87c69", null ]
];