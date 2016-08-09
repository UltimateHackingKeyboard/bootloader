var group__lpi2c__master__driver =
[
    [ "lpi2c_master_config_t", "group__lpi2c__master__driver.html#structlpi2c__master__config__t", [
      [ "baudRate_Hz", "group__lpi2c__master__driver.html#a641b4c5a540819b16faf80c811ac06af", null ],
      [ "busIdleTimeout_ns", "group__lpi2c__master__driver.html#a961dbf85b56b5bf19ba9cafcba0df58d", null ],
      [ "debugEnable", "group__lpi2c__master__driver.html#aeb6e12d340808e4933c3abd23693d8c3", null ],
      [ "enableDoze", "group__lpi2c__master__driver.html#adc33c54dc06ce1822fe921591e5b4d8a", null ],
      [ "enableMaster", "group__lpi2c__master__driver.html#ab8b96ba3ced8b280ac1f366f6e76a9e7", null ],
      [ "hostRequest", "group__lpi2c__master__driver.html#aa7687110e4aa454048405f4a97d5308b", null ],
      [ "ignoreAck", "group__lpi2c__master__driver.html#a0c9caf9d8740154459a3cdff687e8d3c", null ],
      [ "pinConfig", "group__lpi2c__master__driver.html#ad7bda7c48ed142e29bdd31a35248e33f", null ],
      [ "pinLowTimeout_ns", "group__lpi2c__master__driver.html#a33ce3a40b430de3ff3f749ea579a52a9", null ],
      [ "sclGlitchFilterWidth_ns", "group__lpi2c__master__driver.html#ae2137ef7d80c5a9e3de80542f85db11d", null ],
      [ "sdaGlitchFilterWidth_ns", "group__lpi2c__master__driver.html#a46240a7c670a6ad0665c437bbe89d4a3", null ]
    ] ],
    [ "lpi2c_master_config_t.hostRequest", "group__lpi2c__master__driver.html#structlpi2c__master__config__t_8host_request", [
      [ "enable", "group__lpi2c__master__driver.html#a208f156d4a803025c284bb595a7576b4", null ],
      [ "polarity", "group__lpi2c__master__driver.html#abf26cfe05f05fa0ee79497b6441582b9", null ],
      [ "source", "group__lpi2c__master__driver.html#a36cd38f49b9afa08222c0dc9ebfe35eb", null ]
    ] ],
    [ "lpi2c_data_match_config_t", "group__lpi2c__master__driver.html#structlpi2c__data__match__config__t", [
      [ "match0", "group__lpi2c__master__driver.html#aa030e77206dc6105fc07b15a5fee926f", null ],
      [ "match1", "group__lpi2c__master__driver.html#a9ba32b2ddf6b2388ac4b99031ed54354", null ],
      [ "matchMode", "group__lpi2c__master__driver.html#ad70b1ba40d25fd8bc0d2674476ec5c91", null ],
      [ "rxDataMatchOnly", "group__lpi2c__master__driver.html#aea5fb485eeecf79a51312f36205b4b08", null ]
    ] ],
    [ "lpi2c_master_transfer_t", "group__lpi2c__master__driver.html#struct__lpi2c__master__transfer", [
      [ "data", "group__lpi2c__master__driver.html#a735984d41155bc1032e09bece8f8d66d", null ],
      [ "dataSize", "group__lpi2c__master__driver.html#a78f9703861dd365a513c2c5aab9f9239", null ],
      [ "direction", "group__lpi2c__master__driver.html#af44b4d270443cdc17ab6b163a3b89999", null ],
      [ "flags", "group__lpi2c__master__driver.html#a773b39d480759f67926cb18ae2219281", null ],
      [ "slaveAddress", "group__lpi2c__master__driver.html#a67af74c3fc959654c6dc8bcff3a2ea80", null ],
      [ "subaddress", "group__lpi2c__master__driver.html#a6fbfb5e5018422a177a9f3ed7269b127", null ],
      [ "subaddressSize", "group__lpi2c__master__driver.html#aaaef09a4b58df0f2e4f9df16e63bd305", null ]
    ] ],
    [ "lpi2c_master_handle_t", "group__lpi2c__master__driver.html#struct__lpi2c__master__handle", [
      [ "buf", "group__lpi2c__master__driver.html#a2c5f4ef732286b78e31ec8d1cb238215", null ],
      [ "commandBuffer", "group__lpi2c__master__driver.html#a604532d53d990d7bf4ed16f51edb1cad", null ],
      [ "completionCallback", "group__lpi2c__master__driver.html#a901a46c284a787e7871e147806f7776a", null ],
      [ "remainingBytes", "group__lpi2c__master__driver.html#ac76c70a094e7bb19294fe4b0a942d4e5", null ],
      [ "state", "group__lpi2c__master__driver.html#a0b57aa10271a66f3dc936bba1d2f3830", null ],
      [ "transfer", "group__lpi2c__master__driver.html#ac4d8307bc87763e50d8d5012fa20c85d", null ],
      [ "userData", "group__lpi2c__master__driver.html#a2e294dd14122c554baa0665072b4ca7a", null ]
    ] ],
    [ "lpi2c_master_transfer_callback_t", "group__lpi2c__master__driver.html#gac848c547c21a9929224af938c57bdc2e", null ],
    [ "_lpi2c_master_flags", "group__lpi2c__master__driver.html#ga830bba7ea584a7f98d3fb6afd946d739", [
      [ "kLPI2C_MasterTxReadyFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739af3208f156244a4b1c520db35b147ee33", null ],
      [ "kLPI2C_MasterRxReadyFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739ae09650509ffef3de4ede348c4ac66be5", null ],
      [ "kLPI2C_MasterEndOfPacketFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739adf431b1a9475437d7089df5abcea7122", null ],
      [ "kLPI2C_MasterStopDetectFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739aad8d90df6216a4d27680fd530c42710d", null ],
      [ "kLPI2C_MasterNackDetectFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739a3ea7b4560b395c82e5293678228fff81", null ],
      [ "kLPI2C_MasterArbitrationLostFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739a9e012e945342b8f0333e59060affb0b1", null ],
      [ "kLPI2C_MasterFifoErrFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739aac4e2ec9c92ea22b5246bb62000f93a9", null ],
      [ "kLPI2C_MasterPinLowTimeoutFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739a37ceb9a9bdaa1ec7261d7265a51a5f17", null ],
      [ "kLPI2C_MasterDataMatchFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739aaaad4c02a63dcf7d021baa5c4a9dcf2e", null ],
      [ "kLPI2C_MasterBusyFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739ac1de9e29d8ffe76b10b8425f81db1368", null ],
      [ "kLPI2C_MasterBusBusyFlag", "group__lpi2c__master__driver.html#gga830bba7ea584a7f98d3fb6afd946d739a408ed7773539a17625803f6c9d3a6629", null ]
    ] ],
    [ "_lpi2c_master_transfer_flags", "group__lpi2c__master__driver.html#ga6d8e7ad8c6f187673a91247a23a52dc1", [
      [ "kLPI2C_TransferDefaultFlag", "group__lpi2c__master__driver.html#gga6d8e7ad8c6f187673a91247a23a52dc1a413ec0da1a0be18365a3ba1285fe78f4", null ],
      [ "kLPI2C_TransferNoStartFlag", "group__lpi2c__master__driver.html#gga6d8e7ad8c6f187673a91247a23a52dc1adc9924923c68af7960d4b8cf43e5609e", null ],
      [ "kLPI2C_TransferRepeatedStartFlag", "group__lpi2c__master__driver.html#gga6d8e7ad8c6f187673a91247a23a52dc1a2d6fdbacf571dc6eea70ef0349c73ccb", null ],
      [ "kLPI2C_TransferNoStopFlag", "group__lpi2c__master__driver.html#gga6d8e7ad8c6f187673a91247a23a52dc1a56c1abdffee0978f6d5aeedba30971c3", null ]
    ] ],
    [ "lpi2c_data_match_config_mode_t", "group__lpi2c__master__driver.html#ga28ac6ee1cc7991c2907abb18adbb1b31", [
      [ "kLPI2C_MatchDisabled", "group__lpi2c__master__driver.html#gga28ac6ee1cc7991c2907abb18adbb1b31a00ef085f1047daf41240a7c9daa7aee5", null ],
      [ "kLPI2C_1stWordEqualsM0OrM1", "group__lpi2c__master__driver.html#gga28ac6ee1cc7991c2907abb18adbb1b31ae41fc9d1480c995ecab8be9afc489108", null ],
      [ "kLPI2C_AnyWordEqualsM0OrM1", "group__lpi2c__master__driver.html#gga28ac6ee1cc7991c2907abb18adbb1b31af994783c76b2008af82fa9209d1fb746", null ],
      [ "kLPI2C_1stWordEqualsM0And2ndWordEqualsM1", "group__lpi2c__master__driver.html#gga28ac6ee1cc7991c2907abb18adbb1b31a309463f537d290dc18770d4245e0046e", null ],
      [ "kLPI2C_AnyWordEqualsM0AndNextWordEqualsM1", "group__lpi2c__master__driver.html#gga28ac6ee1cc7991c2907abb18adbb1b31a747cdb86ebade4b5d09fc25a0f199aee", null ],
      [ "kLPI2C_1stWordAndM1EqualsM0AndM1", "group__lpi2c__master__driver.html#gga28ac6ee1cc7991c2907abb18adbb1b31a1b963126207a01049b68b0fd7645ff4a", null ],
      [ "kLPI2C_AnyWordAndM1EqualsM0AndM1", "group__lpi2c__master__driver.html#gga28ac6ee1cc7991c2907abb18adbb1b31a37e28fca69438b64be9ca862bade372b", null ]
    ] ],
    [ "lpi2c_direction_t", "group__lpi2c__master__driver.html#gaf7540e799ad5eb17c678b39ea1ace80c", [
      [ "kLPI2C_Write", "group__lpi2c__master__driver.html#ggaf7540e799ad5eb17c678b39ea1ace80ca4a913c200cf54c773380ea8271e7b42b", null ],
      [ "kLPI2C_Read", "group__lpi2c__master__driver.html#ggaf7540e799ad5eb17c678b39ea1ace80ca50ba3a53d79baed347bb8fa07d7884ab", null ]
    ] ],
    [ "lpi2c_host_request_polarity_t", "group__lpi2c__master__driver.html#ga78edbfb2d1e9213e7ebfabe32423f5d2", [
      [ "kLPI2C_HostRequestPinActiveLow", "group__lpi2c__master__driver.html#gga78edbfb2d1e9213e7ebfabe32423f5d2aab540d2690ea7446d68f0106e46cfb36", null ],
      [ "kLPI2C_HostRequestPinActiveHigh", "group__lpi2c__master__driver.html#gga78edbfb2d1e9213e7ebfabe32423f5d2a1f72f10b4bfe685cc57e8994df237a16", null ]
    ] ],
    [ "lpi2c_host_request_source_t", "group__lpi2c__master__driver.html#gac9a07c4c7370019ccabc914bd26ea1c8", [
      [ "kLPI2C_HostRequestExternalPin", "group__lpi2c__master__driver.html#ggac9a07c4c7370019ccabc914bd26ea1c8a4634268e7c377ffd2e7db9a93b2776eb", null ],
      [ "kLPI2C_HostRequestInputTrigger", "group__lpi2c__master__driver.html#ggac9a07c4c7370019ccabc914bd26ea1c8a1a8773fbec157bc1a069826af08a2aae", null ]
    ] ],
    [ "lpi2c_master_pin_config_t", "group__lpi2c__master__driver.html#ga07db39ec1d066e1427d7e58a52c7ea12", [
      [ "kLPI2C_2PinOpenDrain", "group__lpi2c__master__driver.html#gga07db39ec1d066e1427d7e58a52c7ea12ada174b660785782567aee14c05918d89", null ],
      [ "kLPI2C_2PinOutputOnly", "group__lpi2c__master__driver.html#gga07db39ec1d066e1427d7e58a52c7ea12a9a8053876d619b3beeb745b212b9a1fb", null ],
      [ "kLPI2C_2PinPushPull", "group__lpi2c__master__driver.html#gga07db39ec1d066e1427d7e58a52c7ea12a53f8d0708cfc2ea887abb2e2d440d29e", null ],
      [ "kLPI2C_4PinPushPull", "group__lpi2c__master__driver.html#gga07db39ec1d066e1427d7e58a52c7ea12a9642890d09eeb5ed0b8d9e59aac6e3b7", null ],
      [ "kLPI2C_2PinOpenDrainWithSeparateSlave", "group__lpi2c__master__driver.html#gga07db39ec1d066e1427d7e58a52c7ea12ad809117a74ffea333e273e97dc93aff7", null ],
      [ "kLPI2C_2PinOutputOnlyWithSeparateSlave", "group__lpi2c__master__driver.html#gga07db39ec1d066e1427d7e58a52c7ea12a297f630d584519da05064b2962596ee5", null ],
      [ "kLPI2C_2PinPushPullWithSeparateSlave", "group__lpi2c__master__driver.html#gga07db39ec1d066e1427d7e58a52c7ea12a5e8d93f3f8f55f5c9a47c7cddd4df495", null ],
      [ "kLPI2C_4PinPushPullWithInvertedOutput", "group__lpi2c__master__driver.html#gga07db39ec1d066e1427d7e58a52c7ea12acb4290916ade8b65741bc18d632acbd6", null ]
    ] ],
    [ "LPI2C_MasterAbortTransfer", "group__lpi2c__master__driver.html#gabcfefd3c2ba36ea55fe4363844f4b5e5", null ],
    [ "LPI2C_MasterClearStatusFlags", "group__lpi2c__master__driver.html#ga27324dea42cdddefdfdf53a034118522", null ],
    [ "LPI2C_MasterConfigureDataMatch", "group__lpi2c__master__driver.html#gae258a7281c9afd04f3b0133430449404", null ],
    [ "LPI2C_MasterCreateHandle", "group__lpi2c__master__driver.html#ga2f097403040b7db23a958c4660004d98", null ],
    [ "LPI2C_MasterDeinit", "group__lpi2c__master__driver.html#ga1e5ac26414d36018ac33f31332026b82", null ],
    [ "LPI2C_MasterDisableInterrupts", "group__lpi2c__master__driver.html#ga50ab891c01b147071d465138b144fce7", null ],
    [ "LPI2C_MasterEnable", "group__lpi2c__master__driver.html#ga46bd9c4d6579fa0273c3a1cc1c94b65a", null ],
    [ "LPI2C_MasterEnableDMA", "group__lpi2c__master__driver.html#ga682c0d77de6725eb842b8bf26d70ef6e", null ],
    [ "LPI2C_MasterEnableInterrupts", "group__lpi2c__master__driver.html#ga41f9e18b131a5a3ed0f0573c468c3123", null ],
    [ "LPI2C_MasterGetBusIdleState", "group__lpi2c__master__driver.html#ga5b26965efb8b28aeedaf4d8e4491fb50", null ],
    [ "LPI2C_MasterGetDefaultConfig", "group__lpi2c__master__driver.html#gaf1753f02b6a39bb4391250c646236eae", null ],
    [ "LPI2C_MasterGetEnabledInterrupts", "group__lpi2c__master__driver.html#ga8894194d00537fa3a5bae2b88910790c", null ],
    [ "LPI2C_MasterGetFifoCounts", "group__lpi2c__master__driver.html#ga485117a5769985079d759dbf083450fd", null ],
    [ "LPI2C_MasterGetRxFifoAddress", "group__lpi2c__master__driver.html#ga84da0ad9e383e1b06ddfce53a52f2777", null ],
    [ "LPI2C_MasterGetStatusFlags", "group__lpi2c__master__driver.html#ga02cab0c6281b9532bd6f8e2b04e5a2ba", null ],
    [ "LPI2C_MasterGetTransferCount", "group__lpi2c__master__driver.html#ga231f9a10aae9d03d7d2185e2fe8e8bf7", null ],
    [ "LPI2C_MasterGetTxFifoAddress", "group__lpi2c__master__driver.html#ga5350c8b782a982c3a2a7103a32a55569", null ],
    [ "LPI2C_MasterHandleInterrupt", "group__lpi2c__master__driver.html#gaee44171139cc29cd50a3df29ee534979", null ],
    [ "LPI2C_MasterInit", "group__lpi2c__master__driver.html#ga31c7e21bae74602cb831109e7de33ade", null ],
    [ "LPI2C_MasterReceive", "group__lpi2c__master__driver.html#ga6a80cb5c1ccdbac0c753f86e8dd4d00d", null ],
    [ "LPI2C_MasterRepeatedStart", "group__lpi2c__master__driver.html#gacd57806adaf72ea3c3506414c3984f84", null ],
    [ "LPI2C_MasterReset", "group__lpi2c__master__driver.html#ga75ac46a8612bfb21b52699a3feb2cd03", null ],
    [ "LPI2C_MasterSend", "group__lpi2c__master__driver.html#ga5a6e1ac09452fc5182b0fd3a0da1d9b3", null ],
    [ "LPI2C_MasterSetBaudRate", "group__lpi2c__master__driver.html#ga7f9f7d0d1c86fb7ee26d84dba706bc9a", null ],
    [ "LPI2C_MasterSetWatermarks", "group__lpi2c__master__driver.html#gaf0eb7016afbb3ab6bf8d624dbc95347d", null ],
    [ "LPI2C_MasterStart", "group__lpi2c__master__driver.html#gad5ec3758566b673bdec4f7030395b863", null ],
    [ "LPI2C_MasterStop", "group__lpi2c__master__driver.html#ga63d65ab0751f91adecb03944b117f3df", null ],
    [ "LPI2C_MasterTransferNonBlocking", "group__lpi2c__master__driver.html#ga2b0c04b87bd15fcaeac176993969bc29", null ]
];