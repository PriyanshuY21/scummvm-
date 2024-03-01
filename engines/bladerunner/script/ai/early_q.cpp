/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "bladerunner/script/ai_script.h"

namespace BladeRunner {

AIScriptEarlyQ::AIScriptEarlyQ(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_varNumOfTimesToHoldCurrentFrame = 0;
	// _varChooseIdleAnimation can have valid values: 0, 1
	_varChooseIdleAnimation = 0;
	_var3 = 1;
	_resumeIdleAfterFramesetCompletesFlag = false;
}

void AIScriptEarlyQ::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;

	_varNumOfTimesToHoldCurrentFrame = 0;
	_varChooseIdleAnimation = 0;
	_var3 = 1;
	_resumeIdleAfterFramesetCompletesFlag = false;
}

bool AIScriptEarlyQ::Update() {
	if ( Global_Variable_Query(kVariableChapter) == 1
	 && !Game_Flag_Query(kFlagEarlyQStartedChapter1)
	) {
		Game_Flag_Set(kFlagEarlyQStartedChapter1);
		Actor_Put_In_Set(kActorEarlyQ, kSetFreeSlotH);
		Actor_Set_At_Waypoint(kActorEarlyQ, 40, 0);
		Actor_Set_Goal_Number(kActorEarlyQ, 0);
		return true;
	}

	if ( Global_Variable_Query(kVariableChapter) == 2
	 && !Game_Flag_Query(kFlagEarlyQStartedChapter2)
	) {
		Game_Flag_Set(kFlagEarlyQStartedChapter2);
		Actor_Put_In_Set(kActorEarlyQ, kSetFreeSlotH);
		Actor_Set_At_Waypoint(kActorEarlyQ, 40, 0);
		Actor_Set_Goal_Number(kActorEarlyQ, 100);
		return true;
	}

	if ( Global_Variable_Query(kVariableChapter) == 3
	 && !Game_Flag_Query(kFlagEarlyQStartedChapter3)
	) {
		Game_Flag_Set(kFlagEarlyQStartedChapter3);
		Actor_Put_In_Set(kActorEarlyQ, kSetFreeSlotH);
		Actor_Set_At_Waypoint(kActorEarlyQ, 40, 0);
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQWalkAround);
		return true;
	}

	return false;
}

void AIScriptEarlyQ::TimerExpired(int timer) {
	if (timer == kActorTimerAIScriptCustomTask0
	 && Actor_Query_Goal_Number(kActorEarlyQ) == kGoalEarlyQNR05WillLeave
	) {
		if (Player_Query_Current_Scene() == kSceneNR05) {
			AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask0);
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05Leave);
		} else {
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05Wait);
		}
		return; //true;
	}

	if (timer == kActorTimerAIScriptCustomTask0
	 && Actor_Query_Goal_Number(kActorEarlyQ) == kGoalEarlyQNR04GoToMcCoy
	) {
		Player_Loses_Control();
		AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask0);
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04HandDrink);
		return; //true;
	}

	if (timer == kActorTimerAIScriptCustomTask1
	 && Actor_Query_Goal_Number(kActorEarlyQ) == kGoalEarlyQNR04WaitForPulledGun
	) {
		AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask1);
		Player_Loses_Control();
		Actor_Change_Animation_Mode(kActorEarlyQ, 29);
		Delay(2500);
		Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
		Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeCombatAttack);
		Delay(100);
		_vm->_aiScripts->callChangeAnimationMode(kActorMcCoy, kAnimationModeCombatHit);
		Delay(250);
		_vm->_aiScripts->callChangeAnimationMode(kActorMcCoy, kAnimationModeDie);
		Actor_Retired_Here(kActorMcCoy, 12, 12, true, -1);

		return; //true;
	}

	return; //false;
}

void AIScriptEarlyQ::CompletedMovementTrack() {
	switch (Actor_Query_Goal_Number(kActorEarlyQ)) {
	case 0:
		if (Random_Query(1, 2) == 1) {
			Actor_Set_Goal_Number(kActorEarlyQ, 1);
		} else {
			Actor_Set_Goal_Number(kActorEarlyQ, 2);
		}
		break;

	case 1:
		// fall through
	case 2:
		Actor_Set_Goal_Number(kActorEarlyQ, 0);
		break;

	case 100:
		if (Random_Query(1, 2) != 1) {
			Actor_Set_Goal_Number(kActorEarlyQ, 102);
			break;
		}
		Actor_Set_Goal_Number(kActorEarlyQ, 101);
		break;

	case 101:
		Actor_Set_Goal_Number(kActorEarlyQ, 100);
		break;

	case 102:
		Actor_Set_Goal_Number(kActorEarlyQ, 100);
		break;

	case kGoalEarlyQNR04Enter:
		Game_Flag_Set(kFlagNR04EarlyQWalkedIn);
		Player_Set_Combat_Mode(false);
		Actor_Set_Targetable(kActorEarlyQ, true);
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Talk1);
		break;

	case kGoalEarlyQNR04GoToBar:
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04PourDrink);
		break;

	case kGoalEarlyQNR05Leave:
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05AnnouceDektora);
		return; //false;

	case kGoalEarlyQNR04Wait:
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQWalkAround);
		return; //false;

	default:
		return; //false;
	}

	return; //true;
}

void AIScriptEarlyQ::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptEarlyQ::ClickedByPlayer() {
	//return false;
}

void AIScriptEarlyQ::EnteredSet(int setId) {
	// return false;
}

void AIScriptEarlyQ::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptEarlyQ::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptEarlyQ::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	if ( Game_Flag_Query(kFlagNR04EarlyQWalkedIn)
	 &&  otherActorId == kActorMcCoy
	 &&  combatMode
	 && !Game_Flag_Query(kFlagNR04McCoyAimedAtEarlyQ)
	) {
		if (!Game_Flag_Query(kFlagNotUsed565)) {
			Game_Flag_Set(kFlagNotUsed565);
		}
		Game_Flag_Set(kFlagNR04McCoyAimedAtEarlyQ);
		AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask0);
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04McCoyPulledGun);
		return; // true;
	}

	if ( Actor_Query_Goal_Number(kActorEarlyQ) == kGoalEarlyQNR04WaitForPulledGun
	 &&  otherActorId == kActorMcCoy
	 && !combatMode
	) {
		if (Game_Flag_Query(kFlagNotUsed565)) {
			Game_Flag_Reset(kFlagNotUsed565);
		}
		AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask1);
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Talk3);
		return; //true;
	}

	return; //false;
}

void AIScriptEarlyQ::ShotAtAndMissed() {
	if (Actor_Query_Goal_Number(kActorEarlyQ) == kGoalEarlyQNR04WaitForPulledGun) {
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04GetShot);
		//return true;
	}
	// return false;
}

bool AIScriptEarlyQ::ShotAtAndHit() {
	if (Actor_Query_Goal_Number(kActorEarlyQ) >= 201
	 && Actor_Query_Goal_Number(kActorEarlyQ) <= 217
	) {
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04GetShot);
		return true;
	}

	return false;
}

void AIScriptEarlyQ::Retired(int byActorId) {
	// return false;
}

int AIScriptEarlyQ::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptEarlyQ::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	switch (newGoalNumber) {
	case 0:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 40, 0);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case 1:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 291, 0);
		AI_Movement_Track_Append(kActorEarlyQ, 285, 0);
		AI_Movement_Track_Append(kActorEarlyQ, 292, 30);
		AI_Movement_Track_Append(kActorEarlyQ, 293, 30);
		AI_Movement_Track_Append(kActorEarlyQ, 294, 30);
		AI_Movement_Track_Append(kActorEarlyQ, 295, 30);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case 2:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 40, 120);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case 100:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 40, 0);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case 101:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 291, 0);
		AI_Movement_Track_Append(kActorEarlyQ, 285, 0);
		AI_Movement_Track_Append(kActorEarlyQ, 292, 30);
		AI_Movement_Track_Append(kActorEarlyQ, 293, 30);
		AI_Movement_Track_Append(kActorEarlyQ, 294, 30);
		AI_Movement_Track_Append(kActorEarlyQ, 295, 30);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case 102:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 40, 120);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case kGoalEarlyQWalkAround:
		AI_Movement_Track_Flush(kActorEarlyQ);
		Actor_Put_In_Set(kActorEarlyQ, kSetFreeSlotH);
		Actor_Set_At_Waypoint(kActorEarlyQ, 40, 0);
		if (Game_Flag_Query(kFlagDektoraIsReplicant)
		 && Game_Flag_Query(kFlagGordoRanAway)
		 && Game_Flag_Query(kFlagLucyRanAway)
		) {
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05Wait);
		} else if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Wait);
		} else {
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05Wait);
		}
		break;

	case kGoalEarlyQNR04Enter:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 40, 0);
		AI_Movement_Track_Append(kActorEarlyQ, 322, 0);
		AI_Movement_Track_Append(kActorEarlyQ, 354, 0);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case kGoalEarlyQNR04GoToBar:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 355, 0);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		Actor_Face_Object(kActorMcCoy, "BAR", true);
		break;

	case kGoalEarlyQNR04GoToMcCoy:
		Loop_Actor_Walk_To_Actor(kActorEarlyQ, 0, 36, false, false);
		AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask0);
		AI_Countdown_Timer_Start(kActorEarlyQ, kActorTimerAIScriptCustomTask0, 4);
		break;

	case kGoalEarlyQNR04McCoyPulledGun:
		Player_Set_Combat_Mode(true);
		Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatIdle);
		_vm->_aiScripts->callChangeAnimationMode(kActorMcCoy, kAnimationModeCombatAim);
		Actor_Says(kActorEarlyQ, 130, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 3400, kAnimationModeCombatAim);
		Actor_Says_With_Pause(kActorEarlyQ, 140, 1.0f, kAnimationModeTalk);
		Actor_Says_With_Pause(kActorEarlyQ, 150, 1.0f, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 3405, kAnimationModeCombatAim);
		Actor_Says(kActorEarlyQ, 160, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 3410, kAnimationModeCombatAim);
		_vm->_aiScripts->callChangeAnimationMode(kActorMcCoy, kAnimationModeCombatIdle);
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 31.22f, 0.0f, 267.51f, 0, true, false, false);
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04SitDown);
		break;

	case kGoalEarlyQNR04ScorpionsCheck:
		if (Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04StungByScorpions);
		} else {
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Talk2);
		}
		break;

	case kGoalEarlyQNR04StungByScorpions:
		Actor_Set_Targetable(kActorEarlyQ, false);
		Game_Flag_Set(kFlagNR04EarlyQStungByScorpions);
		Delay(3500);
		Actor_Change_Animation_Mode(kActorEarlyQ, 76);
		Delay(2000);
		Actor_Set_At_XYZ(kActorEarlyQ, 109.0, 0.0, 374.0, 0);
		Actor_Retired_Here(kActorEarlyQ, 12, 12, true, -1);
		Actor_Voice_Over(4180, kActorVoiceOver);
		Scene_Exits_Enable();
		break;

	case kGoalEarlyQNR04WaitForPulledGun:
		AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask1);
		AI_Countdown_Timer_Start(kActorEarlyQ, kActorTimerAIScriptCustomTask1, 5);
		break;

	case kGoalEarlyQNR04TakeDisk:
		Actor_Says(kActorEarlyQ, 0, kAnimationModeTalk);
		Actor_Says(kActorEarlyQ, 10, kAnimationModeTalk);
		Actor_Says(kActorEarlyQ, 20, kAnimationModeTalk);
		Actor_Clue_Lose(kActorMcCoy, kClueEarlyQsClub);
		Scene_Exits_Enable();
		Player_Gains_Control();
		Game_Flag_Set(kFlagNR01McCoyIsDrugged);
		Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiThrowOutMcCoy);
		break;

	case kGoalEarlyQNR04HandDrink:
		if (Actor_Query_Inch_Distance_From_Actor(kActorMcCoy, kActorEarlyQ) > 36) {
			Loop_Actor_Walk_To_Actor(kActorEarlyQ, kActorMcCoy, 36, false, false);
		}
		Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
		Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
		Actor_Change_Animation_Mode(kActorEarlyQ, 23);
		Scene_Loop_Start_Special(kSceneLoopModeOnce, 2, false);
		Ambient_Sounds_Play_Sound(kSfxDRUGOUT, 50, 99, 0, 0);
		Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyNR04Drink);
		break;

	case kGoalEarlyQNR04GetShot:
		AI_Movement_Track_Flush(kActorEarlyQ);
		Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeDie);
		Delay(250);
		Actor_Set_At_XYZ(kActorEarlyQ, 109.0, 0.0, 374.0, 0);
		Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiNR04Enter);
		Player_Set_Combat_Mode(false);
		break;

	case kGoalEarlyQNR04Leave:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 354, 0);
		AI_Movement_Track_Append(kActorEarlyQ, 322, 0);
		AI_Movement_Track_Append(kActorEarlyQ, 40, 0);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case kGoalEarlyQNR05Wait:
		if (Player_Query_Current_Set() == kSetNR05_NR08) {
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Wait);
		} else {
			Actor_Put_In_Set(kActorEarlyQ, kSetNR05_NR08);
			Actor_Set_At_XYZ(kActorEarlyQ, -671.56f, 0.0f, -287.02f, 849);
		}
		break;

	case kGoalEarlyQNR05WillLeave:
		AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask0);
		AI_Countdown_Timer_Start(kActorEarlyQ, kActorTimerAIScriptCustomTask0, 20);
		break;

	case kGoalEarlyQNR05Leave:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Movement_Track_Append(kActorEarlyQ, 429, 0);
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	case kGoalEarlyQNR05AnnouceDektora:
		if (Player_Query_Current_Scene() == kSceneNR05) {
			Actor_Says(kActorEarlyQ, 670, kAnimationModeTalk);
			Actor_Says(kActorEarlyQ, 690, kAnimationModeTalk);
			Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR08Dance);
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05UnlockNR08);
			Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiNR08WatchShow);
		} else {
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05Wait);
		}
		break;

	case kGoalEarlyQNR05UnlockNR08:
		Game_Flag_Set(kFlagNR08Available);
		break;

	case 229:
		AI_Movement_Track_Flush(kActorEarlyQ);
		AI_Countdown_Timer_Reset(kActorEarlyQ, kActorTimerAIScriptCustomTask0);
		break;

	case kGoalEarlyQNR04Wait:
		AI_Movement_Track_Flush(kActorEarlyQ);
		if (Random_Query(1, 3) > 1) {
			AI_Movement_Track_Append(kActorEarlyQ, 322, Random_Query(15, 30));
			AI_Movement_Track_Append(kActorEarlyQ, 39, Random_Query(15, 45));
			AI_Movement_Track_Append(kActorEarlyQ, 40, Random_Query(15, 30));
		} else {
			AI_Movement_Track_Append(kActorEarlyQ, 322, Random_Query(5, 15));
			AI_Movement_Track_Append(kActorEarlyQ, 39, Random_Query(5, 15));
			AI_Movement_Track_Append(kActorEarlyQ, 40, Random_Query(5, 15));
			AI_Movement_Track_Append(kActorEarlyQ, 39, Random_Query(5, 15));
			AI_Movement_Track_Append(kActorEarlyQ, 34, Random_Query(10, 20));
		}
		AI_Movement_Track_Repeat(kActorEarlyQ);
		break;

	default:
		return false;
	}

	return true;
}

bool AIScriptEarlyQ::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case 0:
		if (_varChooseIdleAnimation == 1) {
			*animation = kModelAnimationEarlyQHandOnFace;
			if (_varNumOfTimesToHoldCurrentFrame > 0) {
				--_varNumOfTimesToHoldCurrentFrame;
			} else {
				if (++_animationFrame == 6) {
					_varNumOfTimesToHoldCurrentFrame = Random_Query(8, 15);
				}
				if (_animationFrame < 6) {
					_varNumOfTimesToHoldCurrentFrame = 1;
				}
				if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQHandOnFace)) {
					_animationFrame = 0;
					_varChooseIdleAnimation = 0;
				}
			}
		} else if (_varChooseIdleAnimation == 0) {
			*animation = kModelAnimationEarlyQIdle;
			if (_varNumOfTimesToHoldCurrentFrame > 0) {
				--_varNumOfTimesToHoldCurrentFrame;
				if (!Random_Query(0, 6)) {
					_var3 = -_var3;
				}
			} else {
				_animationFrame += _var3;
				if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQIdle)) {
					_animationFrame = 0;
				}
				if (_animationFrame < 0) {
					_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQIdle) - 1;
				}
				_varNumOfTimesToHoldCurrentFrame = Random_Query(0, 1);
				if (_animationFrame == 0) {
					if (!Random_Query(0, 3)) {
						_varChooseIdleAnimation = 1;
					}
				}
				if (_animationFrame == 0 || _animationFrame == 5) {
					if (Random_Query(0, 1)) {
						_varNumOfTimesToHoldCurrentFrame = Random_Query(2, 8);
					}
				}
			}
		}
		break;

	case 1:
		*animation = kModelAnimationEarlyQSPicksUpBottleAndPoursDrink;
		++_animationFrame;
		if (_animationFrame == 18) {
			Ambient_Sounds_Play_Sound(kSfxBARSFX4, 99, 0, 0, 20);
		}
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			Actor_Change_Animation_Mode(kActorEarlyQ, 74);
			_animationFrame = 0;
			_animationState = 2;
			*animation = kModelAnimationEarlyQSHoldsDrinkIdle;
		}
		break;

	case 2:
		*animation = kModelAnimationEarlyQSHoldsDrinkIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQSHoldsDrinkIdle)) {
			_animationFrame = 0;
		}
		break;

	case 3:
		*animation = kModelAnimationEarlyQGivesSomething;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQGivesSomething)) {
			*animation = kModelAnimationEarlyQIdle;
			_animationFrame = 0;
			_animationState = 0;
			Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeIdle);
		}
		break;

	case 4:
		*animation = kModelAnimationEarlyQDropsDead;
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQDropsDead) - 1) {
			++_animationFrame;
		}
		break;

	case 5:
		*animation = kModelAnimationEarlyQWalking;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQWalking)) {
			_animationFrame = 0;
		}
		break;

	case 6:
		*animation = kModelAnimationEarlyQCombatWalking;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQCombatWalking)) {
			_animationFrame = 0;
		}
		break;

	case 7:
		*animation = kModelAnimationEarlyQSitsAndCrossesLegs;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQSitsAndCrossesLegs)) {
			_animationFrame = 0;
			_animationState = 9;
			*animation = kModelAnimationEarlyQSitIdle;
		}
		break;

	case 8:
		*animation = kModelAnimationEarlyQSitToStandingUp;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQSitToStandingUp)) {
			*animation = kModelAnimationEarlyQIdle;
			_animationFrame = 0;
			_animationState = 0;
		}
		break;

	case 9:
		*animation = kModelAnimationEarlyQSitIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQSitIdle)) {
			_animationFrame = 0;
		}
		break;

	case 10:
		*animation = kModelAnimationEarlyQSitTalk;
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			_resumeIdleAfterFramesetCompletesFlag = false;
			_animationState = 9;
			_varChooseIdleAnimation = 0;
			*animation = kModelAnimationEarlyQSitIdle;
			Actor_Change_Animation_Mode(kActorEarlyQ, 53);
		} else {
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQSitTalk)) {
				_animationFrame = 0;
			}
		}
		break;

	case 11:
		*animation = kModelAnimationEarlyQSitScorpionAgonyDeath;
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQSitScorpionAgonyDeath) - 1) {
			++_animationFrame;
		}
		if (_animationFrame == 1) {
			Ambient_Sounds_Play_Sound(kSfxMALEHURT, 59, 0, 0, 20);
		}
		if (_animationFrame == 8) {
			Ambient_Sounds_Play_Sound(kSfxBARSFX3,  47, 0, 0, 20);
		}
		if (_animationFrame == 11) {
			Ambient_Sounds_Play_Sound(kSfxDROPGLAS, 27, 0, 0, 20);
		}
		if (_animationFrame == 14) {
			Ambient_Sounds_Play_Sound(kSfxZUBLAND1, 41, 0, 0, 20);
		}
		break;

	case 12:
		*animation = kModelAnimationEarlyQCombatIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQCombatIdle)) {
			_animationFrame = 0;
		}
		break;

	case 13:
		*animation = kModelAnimationEarlyQCombatUnholsterGun;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQCombatUnholsterGun)) {
			_animationFrame = 0;
			_animationState = 12;
			*animation = kModelAnimationEarlyQCombatIdle;
		}
		break;

	case 14:
		*animation = kModelAnimationEarlyQCombatHolsterGun;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQCombatHolsterGun)) {
			*animation = kModelAnimationEarlyQIdle;
			_animationFrame = 0;
			_animationState = 0;
		}
		break;

	case 15:
		*animation = kModelAnimationEarlyQCombatFiresGun;
		++_animationFrame;
		if (_animationFrame == 2) {
			Ambient_Sounds_Play_Sound(kSfxLGCAL1, 60, 0, 0, 20);
		}
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQCombatFiresGun)) {
			_animationFrame = 0;
			_animationState = 12;
			*animation = kModelAnimationEarlyQCombatIdle;
			Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeCombatIdle); // TODO: kAnimationModeCombatIdle?
		}
		break;

	case 16:
		*animation = kModelAnimationEarlyQGotHitRight;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQGotHitRight)) {
			*animation = kModelAnimationEarlyQIdle;
			_animationFrame = 0;
			_animationState = 0;
			Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeIdle);
		}
		break;

	case 17:
		*animation = kModelAnimationEarlyQGotHitLeft;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQGotHitLeft)) {
			*animation = kModelAnimationEarlyQIdle;
			_animationFrame = 0;
			_animationState = 0;
			Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeIdle);
		}
		break;

	case 18:
		*animation = kModelAnimationEarlyQGotHitRight;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQGotHitRight)) {
			*animation = kModelAnimationEarlyQIdle;
			_animationFrame = 0;
			_animationState = 0;
			Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeIdle);
		}
		break;

	case 19:
		*animation = kModelAnimationEarlyQGotHitLeft;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQGotHitLeft)) {
			*animation = kModelAnimationEarlyQIdle;
			_animationFrame = 0;
			_animationState = 0;
			Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeIdle);
		}
		break;

	case 20:
		*animation = kModelAnimationEarlyQCalmTalk;
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			*animation = kModelAnimationEarlyQIdle;
			_animationFrame = 0;
			_resumeIdleAfterFramesetCompletesFlag = false;
			_animationState = 0;
		} else {
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQCalmTalk)) {
				_animationFrame = 0;
			}
		}
		break;

	case 21:
		*animation = kModelAnimationEarlyQCalmExplainTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQCalmExplainTalk)) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationEarlyQCalmTalk;
		}
		break;

	case 22:
		*animation = kModelAnimationEarlyQVulgarTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQVulgarTalk)) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationEarlyQCalmTalk;
		}
		break;

	case 23:
		*animation = kModelAnimationEarlyQDismissTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQDismissTalk)) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationEarlyQCalmTalk;
		}
		break;

	case 24:
		*animation = kModelAnimationEarlyQMoreDismissTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQMoreDismissTalk)) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationEarlyQCalmTalk;
		}
		break;

	case 25:
		*animation = kModelAnimationEarlyQIntenseExplainTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQIntenseExplainTalk)) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationEarlyQCalmTalk;
		}
		break;

	case 26:
		*animation = kModelAnimationEarlyQSubtleExplainTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQSubtleExplainTalk)) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationEarlyQCalmTalk;
		}
		break;

	case 27:
		*animation = kModelAnimationEarlyQExcitedTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQExcitedTalk)) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationEarlyQCalmTalk;
		}
		break;

	case 28:
		*animation = kModelAnimationEarlyQAnnounceTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationEarlyQAnnounceTalk)) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationEarlyQCalmTalk;
		}
		break;

	default:
		debugC(6, kDebugAnimation, "AIScriptEarlyQ::UpdateAnimation() - Current _animationState (%d) is not supported", _animationState);
		break;
	}
	*frame = _animationFrame;

	return true;
}

bool AIScriptEarlyQ::ChangeAnimationMode(int mode) {
	switch (mode) {
	case kAnimationModeIdle:
		switch (_animationState) {
		case 1:
			Actor_Change_Animation_Mode(kActorEarlyQ, 73);
			break;

		case 2:
			Actor_Change_Animation_Mode(kActorEarlyQ, 74);
			break;

		case 9:
			Actor_Change_Animation_Mode(kActorEarlyQ, 29);
			break;

		case 10:
			// fall through
		case 20:
			// fall through
		case 21:
			// fall through
		case 22:
			// fall through
		case 23:
			// fall through
		case 24:
			// fall through
		case 25:
			// fall through
		case 26:
			// fall through
		case 27:
			// fall through
		case 28:
			_resumeIdleAfterFramesetCompletesFlag = true;
			break;

		case 12:
			// fall through
		case 13:
			// fall through
		case 15:
			_animationState = 14;
			_animationFrame = 0;
			break;

		case 14:
			return 1;

		default:
			_animationState = 0;
			_animationFrame = 0;
			break;
		}
		break;

	case kAnimationModeWalk:
		_animationState = 5;
		_animationFrame = 0;
		break;

	case kAnimationModeTalk:
		_animationState = 20;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case kAnimationModeCombatIdle:
		if ((unsigned int)(_animationState - 12) > 3
		 || (_animationState != 12
		  && _animationState != 13
		  && _animationState != 15
		 )
		) {
			_animationState = 13;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeCombatAttack:
		_animationState = 15;
		_animationFrame = 0;
		break;

	case kAnimationModeCombatWalk:
		_animationState = 6;
		_animationFrame = 0;
		break;

	case 12:
		_animationState = 21;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 13:
		_animationState = 22;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 14:
		_animationState = 23;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 15:
		_animationState = 24;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 16:
		_animationState = 25;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 17:
		_animationState = 26;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 18:
		_animationState = 27;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 19:
		_animationState = 28;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case kAnimationModeHit:
		if ((unsigned int)(_animationState - 12) > 3
		 || (_animationState != 12
		  && _animationState != 13
		  && _animationState != 15
		 )
		) {
			if (Random_Query(0, 1)) {
				_animationState = 16;
			} else {
				_animationState = 17;
			}
			_animationFrame = 0;
		} else {
			if (Random_Query(0, 1)) {
				_animationState = 18;
			} else {
				_animationState = 19;
			}
			_animationFrame = 0;
		}
		break;

	case 23:
		_animationState = 3;
		_animationFrame = 0;
		break;

	case 29:
		_animationState = 8;
		_animationFrame = 0;
		break;

	case 30:
		_animationState = 10;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case kAnimationModeDie:
		_animationState = 4;
		_animationFrame = 0;
		break;

	case 53:
		_animationState = 9;
		_animationFrame = 0;
		break;

	case 73:
		if (_animationState != 1) {
			_animationState = 1;
			_animationFrame = 0;
		}
		break;

	case 74:
		if (_animationState != 2) {
			_animationState = 2;
			_animationFrame = 0;
		}
		break;

	case 76:
		_animationState = 11;
		_animationFrame = 0;
		break;

	case 85:
		_animationState = 7;
		_animationFrame = 0;
		break;

	default:
		debugC(6, kDebugAnimation, "AIScriptEarlyQ::ChangeAnimationMode(%d) - Target mode is not supported", mode);
		break;
	}

	return true;
}

void AIScriptEarlyQ::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptEarlyQ::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptEarlyQ::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptEarlyQ::FledCombat() {
	// return false;
}

} // End of namespace BladeRunner
