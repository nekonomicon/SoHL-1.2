# SoHL android makefile
# Copyright (c) mittorn



LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := server

include $(XASH3D_CONFIG)

LOCAL_CFLAGS += -D_LINUX -DCLIENT_WEAPONS \
	-Dstricmp=strcasecmp -Dstrnicmp=strncasecmp -D_snprintf=snprintf \
	-Wno-write-strings -Wno-invalid-offsetof -Wno-conversion-null

LOCAL_C_INCLUDES := $(LOCAL_PATH)/. \
		    $(LOCAL_PATH)/../common \
		    $(LOCAL_PATH)/../engine/common \
		    $(LOCAL_PATH)/../engine \
		    $(LOCAL_PATH)/../public \
		    $(LOCAL_PATH)/../pm_shared \
		    $(LOCAL_PATH)/../game_shared \
		    $(LOCAL_PATH)/zombie-x

LOCAL_SRC_FILES := aflock.cpp agrunt.cpp AI_BaseNPC_Schedule.cpp airtank.cpp \
		alias.cpp animating.cpp animation.cpp apache.cpp barnacle.cpp barney.cpp \
		bigmomma.cpp bloater.cpp bmodels.cpp bullsquid.cpp buttons.cpp cbase.cpp \
		client.cpp combat.cpp controller.cpp crossbow.cpp crowbar.cpp defaultai.cpp \
		doors.cpp effects.cpp egon.cpp explode.cpp flyingmonster.cpp func_break.cpp \
		func_tank.cpp game.cpp gamerules.cpp gargantua.cpp gauss.cpp genericmonster.cpp \
		ggrenade.cpp globals.cpp gman.cpp h_ai.cpp handgrenade.cpp hassassin.cpp \
		h_battery.cpp h_cine.cpp h_cycler.cpp headcrab.cpp healthkit.cpp h_export.cpp \
		hgrunt.cpp hornet.cpp hornetgun.cpp houndeye.cpp ichthyosaur.cpp islave_deamon.cpp \
		items.cpp leech.cpp lights.cpp locus.cpp maprules.cpp monstermaker.cpp monsters.cpp \
		monsterstate.cpp mortar.cpp movewith.cpp mp5.cpp multiplay_gamerules.cpp nihilanth.cpp \
		nodes.cpp osprey.cpp pathcorner.cpp plane.cpp plats.cpp player.cpp playermonster.cpp \
		python.cpp rat.cpp roach.cpp rpg.cpp satchel.cpp scientist.cpp scripted.cpp shotgun.cpp \
		singleplay_gamerules.cpp skill.cpp sound.cpp soundent.cpp spectator.cpp squadmonster.cpp \
		squeakgrenade.cpp stats.cpp subs.cpp talkmonster.cpp teamplay_gamerules.cpp tempmonster.cpp \
		tentacle.cpp triggers.cpp tripmine.cpp turret.cpp util.cpp weapons.cpp world.cpp xen.cpp \
		zombie-x/ak47.cpp zombie-x/apache_blackop.cpp zombie-x/auto_shotgun.cpp \
		zombie-x/barney_suit.cpp zombie-x/barniel.cpp zombie-x/bot_combat.cpp zombie-x/bot.cpp \
		zombie-x/botcam.cpp zombie-x/bumplight.cpp zombie-x/debugger.cpp zombie-x/eagel.cpp \
		zombie-x/kate.cpp zombie-x/massn.cpp zombie-x/minigun.cpp zombie-x/mp41a.cpp \
		zombie-x/scientist_suit.cpp zombie-x/shock.cpp zombie-x/shockball.cpp zombie-x/shockgun.cpp \
		zombie-x/swort.cpp zombie-x/teamdm.cpp zombie-x/torch.cpp zombie-x/uzi.cpp \
		zombie-x/zombie_barney.cpp zombie-x/zombie_gus.cpp zombie-x/zombie_soldier.cpp \
		zombie.cpp wpn_shared/hl_wpn_glock.cpp \
	   ../pm_shared/pm_debug.c ../pm_shared/pm_math.c ../pm_shared/pm_shared.c



ifeq ($(TARGET_ARCH_ABI),armeabi-v7a-hard)
LOCAL_MODULE_FILENAME = libserver_hardfp
endif

LOCAL_CPPFLAGS := $(LOCAL_CFLAGS)

include $(BUILD_SHARED_LIBRARY)
