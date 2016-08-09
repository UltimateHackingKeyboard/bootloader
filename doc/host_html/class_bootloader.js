var class_bootloader =
[
    [ "EraseOption", "class_bootloader.html#struct_bootloader_1_1_erase_option", [
      [ "ERASE_OPERATION", "class_bootloader.html#afc77e694fe430cfd1542ca42b65ec5bd", [
        [ "erase_region", "class_bootloader.html#afc77e694fe430cfd1542ca42b65ec5bdab603571ad734a48b9a998b442a79af48", null ],
        [ "erase_all", "class_bootloader.html#afc77e694fe430cfd1542ca42b65ec5bdaaae77abe9884dcce79104c41dd10a88c", null ],
        [ "erase_all_and_unsecure", "class_bootloader.html#afc77e694fe430cfd1542ca42b65ec5bda7bbbd10fd6509b54a0bb185f54d4809c", null ]
      ] ],
      [ "length", "class_bootloader.html#a03d9c27981fcffbf965bd4b0f25f52e2", null ],
      [ "memoryID", "class_bootloader.html#ac89e86493a1ede1a4a7982b3cca5dd42", null ],
      [ "option", "class_bootloader.html#a75de26982d72af4dd0eb2d6bde28d22f", null ],
      [ "startAddress", "class_bootloader.html#aff2c0ac0aafa00b32df1bd72b6928078", null ]
    ] ],
    [ "FlashFirmwareOption", "class_bootloader.html#struct_bootloader_1_1_flash_firmware_option", [
      [ "autoConnect", "class_bootloader.html#a51bf67a9c43de86a7b3b27d0edd522bf", null ],
      [ "backdoorkey", "class_bootloader.html#a943e147e9f6060bbd2538afd805c599a", null ],
      [ "baseAddress", "class_bootloader.html#a90b80490be669a57e2856f6b6abac71c", null ],
      [ "doErasetoUnlock", "class_bootloader.html#a8037e3b401b7cfb870dffbf990022450", null ],
      [ "imageFilePath", "class_bootloader.html#a4962c81431e171b5b9a06a0cd91c5965", null ],
      [ "useKeytoUnlock", "class_bootloader.html#a43a1807310a07b446d9f730f5572afab", null ]
    ] ],
    [ "ProgramOnceOption", "class_bootloader.html#struct_bootloader_1_1_program_once_option", [
      [ "byteCount", "class_bootloader.html#ad4439cf577d66d4ef577d4756d90089b", null ],
      [ "data", "class_bootloader.html#a58ffd3fe5539fc0ec5b53c8bbb1cdb17", null ],
      [ "index", "class_bootloader.html#a32c8470a7d53f90032e0947fc5832a7f", null ]
    ] ],
    [ "TargetInformation", "class_bootloader.html#struct_bootloader_1_1_target_information", [
      [ "flashSectorSize", "class_bootloader.html#a4f445326e13d7cf8df29935ad5e5c48f", null ],
      [ "flashSize", "class_bootloader.html#aeb890355cd8c0f5cea05b76af207619b", null ],
      [ "procotolVersion", "class_bootloader.html#a24f6db9423221fc5e419c97d4fb08cd8", null ],
      [ "ramSize", "class_bootloader.html#a29f25c3ab5c62efdc180be14d33cef5c", null ],
      [ "rsvRgnFlashEnd", "class_bootloader.html#ada65d157f0964c4333da07343159d895", null ],
      [ "rsvRgnFlashStart", "class_bootloader.html#aeb235cb088160afed5b8202210a43a54", null ],
      [ "rsvRgnRamEnd", "class_bootloader.html#a8feaf26140bcb29075bfd287796ac6d8", null ],
      [ "rsvRgnRamStart", "class_bootloader.html#a3449858ac8c33f2e25429a29c13b0cc6", null ],
      [ "securityState", "class_bootloader.html#a5e85f010cbc797b92c613d73ce769648", null ],
      [ "supportedCmd", "class_bootloader.html#a26f5dde51546d578757b7cc578b5829e", null ],
      [ "targetVersion", "class_bootloader.html#a46bd39cca6931b9edea0433febb13e8d", null ]
    ] ],
    [ "KibbleStatusCode", "class_bootloader.html#add067f1d2ddb028a1f9507dc4b10e250", [
      [ "KBL_Status_Success", "class_bootloader.html#add067f1d2ddb028a1f9507dc4b10e250ab2f8dc21e4e8942369162d1b1ec530ba", null ],
      [ "KBL_Status_AbortDataPhase", "class_bootloader.html#add067f1d2ddb028a1f9507dc4b10e250a072e7f2aede63c5dd48ad55bcaff25d2", null ]
    ] ],
    [ "Bootloader", "class_bootloader.html#a4d576bc36952fcec62139e4b14446f31", null ],
    [ "~Bootloader", "class_bootloader.html#a38669b400ae2fc9f4eafb4499acc917b", null ],
    [ "CanRun", "class_bootloader.html#a4af273205d8076cc503bb711078d3186", null ],
    [ "Close", "class_bootloader.html#abee3fbf3d3300823337b9329d6591aba", null ],
    [ "Connect", "class_bootloader.html#a308d15500c36b6b43aaa7ffa0d62e5e9", null ],
    [ "Erase", "class_bootloader.html#a4f9a6e8ab15aced8e181c757a55b27e0", null ],
    [ "ExitInstance", "class_bootloader.html#a57770d6bbbd018c571fbdba193b3984e", null ],
    [ "InitInstance", "class_bootloader.html#a50ffe679128e14abdb12a0a6ae900414", null ],
    [ "Open", "class_bootloader.html#a61ab10abefe9d1f732cd9f5f856ff7db", null ],
    [ "Ping", "class_bootloader.html#afa5a1e11c893f0b0753af8a58d22663a", null ],
    [ "ProgramOnce", "class_bootloader.html#a905ea231625fc3d1cf0590bf07ea7414", null ],
    [ "progressCallback", "class_bootloader.html#a1a46e068401b15ebf9df274364717343", null ],
    [ "Reset", "class_bootloader.html#a133c929da95b4eb3146aadc9263ddb7a", null ],
    [ "ResetEvents", "class_bootloader.html#a5424177076709a46fe6c9e857b0e205c", null ],
    [ "UpdateImage", "class_bootloader.html#ab924c928e84f397d12ff6d46973a8667", null ],
    [ "UpdateStatus", "class_bootloader.html#ac3b047223d7da4311f1303192e9ac6b7", null ],
    [ "WaitForEvents", "class_bootloader.html#ae3ba113f184b63873c0cbe8c7c980791", null ],
    [ "m_abort", "class_bootloader.html#a78a767963a5f9466e40da32cd828fd2c", null ],
    [ "m_config", "class_bootloader.html#ace9b8276b901ec7f886ad9157802102c", null ],
    [ "m_connectEvent", "class_bootloader.html#a5f4d159d8878c69fde40c68b59c9d01b", null ],
    [ "m_eraseEvent", "class_bootloader.html#abc4b9381a2b0a834cfbc52f12f7ed9d8", null ],
    [ "m_eraseOption", "class_bootloader.html#ac991c28688922be7df303e6ed4b92907", null ],
    [ "m_exitEvent", "class_bootloader.html#ac30017b32122088a47be9878d222f46b", null ],
    [ "m_firmwareConfig", "class_bootloader.html#acd69ec17995c8ddb245854e5a1077521", null ],
    [ "m_isConneted", "class_bootloader.html#a0fbc58cf1fefe7fc4ac3e947a52b4afa", null ],
    [ "m_isExiting", "class_bootloader.html#a299608c3c0512aba8bc73c07bd9d0c85", null ],
    [ "m_isRunning", "class_bootloader.html#aed066c866e6476c7cc95ae9e00b5d86c", null ],
    [ "m_pingEvent", "class_bootloader.html#aca9c69e2bff2114569318daf482e55db", null ],
    [ "m_programOnceEvent", "class_bootloader.html#a9fe40f1f702d968b0787f38f6d0c346b", null ],
    [ "m_programOnceOption", "class_bootloader.html#a5cda33a94e2a69b3299a5d9fa015f50e", null ],
    [ "m_pThread", "class_bootloader.html#aeab57f444e845fff5c9499cd5a74d19e", null ],
    [ "m_resetEvent", "class_bootloader.html#a8c681d634a50ff767c6930ac58af35f3", null ],
    [ "m_statusEvent", "class_bootloader.html#a81bf397af7a5668a7a92705ae0f78e56", null ],
    [ "m_targetInfo", "class_bootloader.html#aafef0e47d402f958bcbe6838f48838ce", null ],
    [ "m_updateEvent", "class_bootloader.html#af87a527bf8b42fbb526f8a0b0d6659ee", null ],
    [ "m_updater", "class_bootloader.html#afd1e8fbddcb4bf6b34e01561c463e3df", null ]
];