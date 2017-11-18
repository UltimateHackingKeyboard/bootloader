#!/usr/bin/env node
const fs = require('fs');
require('shelljs/global');

config.fatal = true;
config.verbose = true;

const bootloaderHex = `${__dirname}/../targets/MK22F51212/kds/freedom_bootloader/release/freedom_bootloader.hex`;
const targetConfigH = `${__dirname}/../targets/MK22F51212/src/target_config.h`
const targetConfigHContent = fs.readFileSync(targetConfigH, 'utf8');

const majorNumber = targetConfigHContent.match(/kTarget_Version_Major = ([0-9]+)/)[1];
const minorNumber = targetConfigHContent.match(/kTarget_Version_Minor = ([0-9]+)/)[1];
const patchNumber = targetConfigHContent.match(/kTarget_Version_Bugfix = ([0-9]+)/)[1];

rm('-f', bootloaderHex);

exec(`/opt/Freescale/KDS_v3/eclipse/kinetis-design-studio \
--launcher.suppressErrors \
-noSplash \
-application org.eclipse.cdt.managedbuilder.core.headlessbuild \
-import ${__dirname}/../targets/MK22F51212/kds/freedom_bootloader \
-cleanBuild freedom_bootloader`
);

cp(bootloaderHex, `uhk-bootloader-${majorNumber}.${minorNumber}.${patchNumber}.hex`);
