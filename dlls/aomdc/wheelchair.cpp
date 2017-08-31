/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   This source code contains proprietary and confidential information of
*   Valve LLC and its suppliers.  Access to this code is restricted to
*   persons who have executed a written SDK license with Valve.  Any access,
*   use or distribution of this code by or to any unlicensed person is illegal.
*
****/
//=========================================================
// Wheelchair monster
//=========================================================

#include	"zombie.h"

#define WHEELCHAIR_AE_BLOODSQUIRT		1
#define WHEELCHAIR_AE_WALK			1011

extern short g_sModelIndexBloodSpray;

class CWheelchair : public CZombie
{
public:
	void Spawn( void );
	void Precache( void );
	void HandleAnimEvent( MonsterEvent_t *pEvent );

	float m_flNextFlinch;

	void PainSound( void );
	void AlertSound( void );
	void IdleSound( void );
	void AttackSound( void );

	static const char *pIdleSounds[];
	int vomit;
};

LINK_ENTITY_TO_CLASS( monster_wheelchair, CWheelchair );

const char *CWheelchair::pIdleSounds[] = 
{
	"wheelchair/wheel01.wav",
	"wheelchair/wheel02.wav",
	"wheelchair/wheel03.wav",
	"wheelchair/wheel04.wav"
};

void CWheelchair :: PainSound( void )
{
}

void CWheelchair :: AlertSound( void )
{
}

void CWheelchair :: IdleSound( void )
{
	int pitch = 95 + RANDOM_LONG(0,9);

	// Play a random idle sound
	EMIT_SOUND_DYN ( ENT(pev), CHAN_VOICE, pIdleSounds[ RANDOM_LONG(0,ARRAYSIZE(pIdleSounds)-1) ], 1.0, ATTN_NORM, 0, 100 + RANDOM_LONG(-5,5) );
}

void CWheelchair :: AttackSound( void )
{
}


//=========================================================
// HandleAnimEvent - catches the monster-specific messages
// that occur when tagged animation frames are played.
//=========================================================
void CWheelchair :: HandleAnimEvent( MonsterEvent_t *pEvent )
{
	switch( pEvent->event )
	{
		case WHEELCHAIR_AE_WALK:
			IdleSound();
			break;
		case WHEELCHAIR_AE_BLOODSQUIRT:
		{
			// do stuff for this event.
			CBaseEntity *pHurt = CheckTraceHullAttack( 70, gSkillData.wheelchairDmgAttack, DMG_SLASH );
			if ( pHurt )
			{
				if ( pHurt->pev->flags & (FL_MONSTER|FL_CLIENT) )
				{
					EMIT_SOUND_DYN ( ENT(pev), CHAN_WEAPON, "wheelchair/wcm_squirt.wav", 1.0, ATTN_NORM, 0, 100 + RANDOM_LONG(-5,5) );

					MESSAGE_BEGIN( MSG_PVS, SVC_TEMPENTITY, pev->origin );
						WRITE_BYTE( TE_BLOODSPRITE );
						WRITE_COORD( pev->origin.x );	// pos
						WRITE_COORD( pev->origin.y );
						WRITE_COORD( pev->origin.z );
						WRITE_SHORT( g_sModelIndexBloodSpray );	// sprite1
						WRITE_SHORT( vomit );			// sprite2
						WRITE_BYTE ( 70 ); // color
						WRITE_BYTE ( 10 ); // count
					MESSAGE_END();
					pHurt->pev->punchangle.z = -18;
					pHurt->pev->punchangle.x = 5;
				}
			}

		}
			break;
		default:
			CBaseMonster::HandleAnimEvent( pEvent );
			break;
	}
}

//=========================================================
// Spawn
//=========================================================
void CWheelchair :: Spawn()
{
	Precache( );

	if (pev->model)
		SET_MODEL(ENT(pev), STRING(pev->model)); //LRC
	else
		SET_MODEL(ENT(pev), "models/wheelchair_monster.mdl");
	UTIL_SetSize( pev, VEC_HUMAN_HULL_MIN, VEC_HUMAN_HULL_MAX );

	pev->solid			= SOLID_SLIDEBOX;
	pev->movetype		= MOVETYPE_STEP;
	m_bloodColor		= BLOOD_COLOR_RED;
	if (pev->health == 0)
		pev->health			= gSkillData.wheelchairHealth;
	pev->view_ofs		= VEC_VIEW;// position of the eyes relative to monster's origin.
	m_flFieldOfView		= 0.5;// indicates the width of this monster's forward view cone ( as a dotproduct result )
	m_MonsterState		= MONSTERSTATE_NONE;
	m_afCapability		= bits_CAP_DOORS_GROUP;

	MonsterInit();
}

//=========================================================
// Precache - precaches all resources this monster needs
//=========================================================
void CWheelchair :: Precache()
{
	int i;
	vomit = PRECACHE_MODEL("sprites/wheelchair_vomit.spr");
	if (pev->model)
		PRECACHE_MODEL((char*)STRING(pev->model)); //LRC
	else
		PRECACHE_MODEL("models/wheelchair_monster.mdl");

	PRECACHE_SOUND( "wheelchair/wcm_squirt.wav" );

	for ( i = 0; i < ARRAYSIZE( pIdleSounds ); i++ )
		PRECACHE_SOUND((char *)pIdleSounds[i]);
}	

//=========================================================
// AI Schedules Specific to this monster
//=========================================================
