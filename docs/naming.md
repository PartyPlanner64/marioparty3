# Symbol Naming Conventions

Guidelines for replacing placeholder names (`func_80XXXXXX_seg`, `D_80XXXXXX_seg`)
with purposeful names. The style follows Hudson's own naming, as recovered from
the Mario Party 4 symbol map (engine/board) and Mario Party 7 (`MB`/`Masu` board
naming).

## Grammar

**Functions: `Prefix` + noun phrase + verb last.**

`MBPlayerMotionSpeedSet`, `HuSprAttrSet`, `MBItemKinokoExec` — never
`SetPlayerMotionSpeed` or `CalcLerp`.

Preferred trailing verbs, in Hudson's frequency order:

| Verb | Meaning |
|---|---|
| `Set` / `Get` | write / read a value |
| `Create` / `Kill` | allocate+start / stop+free an object, model, sprite, process |
| `Init` / `Close` | set up / tear down a subsystem |
| `Exec` | run a sequence to completion (usually a blocking process body) |
| `Main` | per-frame update function of an object or process |
| `Check` | returns a boolean answer |
| `Reset`, `Start`, `Stop`, `Wait`, `Add`, `Calc`, `Load`, `Read`, `Update`, `Draw`, `Hook`, `Clear` | as named |
| `On` / `Off` | `DispOn`, `DispOff` style toggles |

Suffixes: `V` = takes a `Vec *` (`PosSetV`); `Ex` = extended variant;
`All` = applies to every instance (`MBStarGuideCreateAll`).

**Data: lowerCamel ending in a type word.**

| Suffix | Meaning |
|---|---|
| `Tbl` | table/array of values |
| `Obj` | `omObjData *` |
| `Proc` | `Process *` |
| `Mdl`, `Spr`, `Mot`, `Grp` | model / sprite / motion / group id |
| `F` | flag (`motDoneF`) |
| `Pos`, `Rot`, `Ofs`, `Scale` | vectors / offsets |
| `No`, `Num`, `Cnt`, `Idx` | id number / count / counter / index |
| `Work` | per-object work struct |
| `Param` | parameter block |
| `Str` / `Mes` | string / message id |

## Prefixes

Every overlay is linked into one ELF, so overlay-local names need an
overlay-unique prefix. Library-wide prefixes have no underscore; per-overlay
prefixes are followed by `_`.

| Scope | Functions | Data |
|---|---|---|
| main segment | existing engine prefixes (`Hu*`, `Hu3D*`, `HuSpr*`, `HuWin*`, `om*`, `esp*`, `GW*`, ...) | lowerCamel, matching the subsystem (`omSysTimerObj`, `hu3DCamera...`) |
| `minigame` (minigames/common) | `Mg` | `mg` |
| `shared_board` (party/common) | `MB` | `mb` |
| `name_81` (duel/common) | `MBD` | `mbd` |
| party board `wNN` | `MB<n>_` (`MB1_` ... `MB6_`, `MB10_`) | `mb<n>_` |
| party board events | `MB<n>Ev_` | `mb<n>ev_` |
| duel board `duelNN` | `MBD<n>_` (`MBD1_` ... `MBD6_`, `MBD10_`) | `mbd<n>_` |
| minigame overlay index `0xNN` | `m2DD_` where `DD` is the overlay index in **decimal** (`0x0D` pump_pump_away -> `m213_`, `0x36` motor_rooter -> `m254_`) | `m2DD_` |
| opening | `op_` | `op_` |
| any other overlay | `<segment name>_` (`filesel_`, `mstory1_`, `chancetime_`, `mgresultboard_`, ...) | same |

After the prefix and `_`, functions use UpperCamel and data uses lowerCamel:
`m213_PlayerObjMain`, `m213_playerObj`, `MB1_BankCoinCreate`, `mb1_bankCoinMdl`.

## Standard role names

These names should be used for these roles in every overlay:

| Role | Name |
|---|---|
| Overlay entry stub at the start of the overlay (calls the setup function, or `ovlEventCall`) | `<prefix>_Executor` |
| `OvlEntrypoint` table passed to `ovlEventCall` | `<prefix>_ovlEntryTbl` |
| Function that initializes the overlay (`omInitObjMan`, cameras, lights, spawns the first objects) | `<prefix>_ObjectSetup` |
| Function passed to `omAddObj` | `<prefix>_<Thing>ObjMain` |
| Function that calls `omAddObj` to make one object | `<prefix>_<Thing>ObjCreate` |
| Process body passed to `HuPrcCreate`/`omAddPrcObj` | `<prefix>_<Thing>Proc` or `<Thing>Exec` |
| Destructor/kill hook | `<prefix>_<Thing>Destroy` |
| Display list / render callback | `<prefix>_<Thing>Draw` |
| Event-space handler on a board | `MB<n>Ev_<Thing>` |
| Board CPU decision tree (`DecisionTreeNonLeafNode[]`) | `mb<n>ev_<Where>ComTree` |
| Board event table (`event_list_entry[]`) | `mb<n>_<Thing>EventTbl` |
| Board branch link table (`BranchLink`) | `mb<n>ev_<Where>Link` |

## Glossary

Use one term per concept. Board code uses Hudson's Japanese-derived nouns.

| Term | Meaning |
|---|---|
| `Masu` | board space |
| `Sai` | dice block (`MBSai*`, per-player `SaiWork` in `mbSaiWorkTbl`, `mbSaiBtnF`; never `Dice`) |
| `Teresa` | Boo |
| `Kinoko` | mushroom (keep the existing `NKinoko`, `RKinoko`, `SKinoko` variant names) |
| `Koopa` | Bowser (`KSuit` = Bowser suit) |
| `Kuribo` | Goomba |
| `Hatena` | `?` space / `?` event |
| `Kettou` | duel (item/event) |
| `MajinLamp` | Lucky lamp / genie lamp |
| `Telop` | on-screen caption banner |
| `Dlg` | dialog window |
| `Com` | CPU-controlled player logic |
| `Mg` | minigame |
| `Mes` | message (text id) |
| `Spr` / `Mdl` / `Mot` | sprite / model / motion |
| `Eff` | effect |
| `Se` / `Mus` | sound effect / music |
| `Win` | window |
| `Wipe` | screen transition |
| `Kinopio` | Toad (item-space host, shops) |
| `KoopaJr` | Baby Bowser |
| `Kakusi` | hidden block (`MBKakusiStarBlockCreate`, existing `kakusiMasu*` data) |
| `Gamble` | Game Guy (space / minigames) |
| `ComKey` | scripted CPU key presses for message windows (`MBWinComKeyWait`) |
| `Pad` (data suffix) | unreferenced BSS/data gap, named after its subsystem (`mbMasuBlockPad`) |
| `Alt` | alternate table selected by a game flag when its meaning is unknown |
| `MgPack` / `Easy` | minigame pack setting (flag 0x20, story flag 0x29; msetup `MgPack*`); when set, minigame selection uses the smaller easy-pack lists (`mbMgCall4PEasyTbl`, `mbMgCallHisLenEasyTbl`, duel `mbdMgCall1vs1EasyTbl`, `mbdMgCallPackOfs`) that leave out mashing/stick-rotation games |
| `Partner` | duel-mode partner (`MBDPartnerSet`, `mbdPartnerObj`); `Front` / `Back` = the two partner slots |
| `Nokonoko` / `Bomhei` / `Pakkun` / `Wanwan` / `Dossun` | duel partners Koopa Troopa / Bob-omb / Piranha Plant / Chain Chomp / Thwomp (`Koopa` stays Bowser); Whomp, Snifit and Mr. Blizzard use `Whomp`, `Snifit`, `Blizzard` |
| `Attack` | duel partner attack sequence (`MBDPartnerAttackExec`, `mbdAttackHp`) |
| `MasuOwner` | duel space ownership by a player (`MBDMasuOwnerAdd`) |
| `Tumble` | the dice-faced host (model 0xA0075; story mode, minigame instructions) |
| `Stamp` | Star Stamp (story-mode chapter reward) |
| `Killer` | Bullet Bill (Hudson name, from debug text in crazy_cogs) |

## Sources, in order of trust

1. Text in MP3 itself (debug strings, overlay/file names).
2. Real symbols from the MP4 map (`../marioparty4/config/GMPE01_00/symbols.txt`) or MP7
   (`../marioparty7/config/GP7E01/symbols.txt`) for code that clearly does the same thing.
3. Names from the MP1/MP2 decomp projects.
4. A new name in the grammar above.

Do not put addresses in new names. If a function's exact purpose is unclear,
pick a role-based name from what it touches (`m213_PumpObjMain`) rather than
leaving a placeholder or inventing a generic `Unk` name.

Functions that were copied into several overlays should share a base name
across overlays (`m254_LerpCalc`, `m255_LerpCalc`). Use
`tools/coddog match <name> -t 0.99 2>/dev/null` to find copies.

## Tooling

`tools/rename_symbols.py MAPFILE` applies `old new` pairs across `src/`,
`include/`, `undefined_syms.txt`, and `symbol_addrs.txt` (adding entries with
`segment:`/`rom:` as needed). It refuses names that already exist. Verify with
`./tools/build.sh --splat`.

### Window wait variants (shared_board)

`MBWin*KeyWait` waits until the window closes; `...WaitKeep` returns once the
message has finished drawing and leaves the window open. `AllKey` variants let
any human player advance the window.

### Assembler quirk

The GCC 2.7.2 toolchain's assembler occasionally emits a stray 4-byte word at
the start of `.text` depending on the exact byte layout of the generated `.s`
file (seen with `MBMotionRefInit` in party/common/model.c). If a pure rename
breaks the match with a shifted segment, try a slightly different name length.

### Duel board library (name_81)

`name_81` mirrors `shared_board`: functions that are copies of an `MB*`
function use the same base name with `MBD` (`MBMasuGet` -> `MBDMasuGet`,
`MBPlayerGet` -> `MBDPlayerGet`, `MBPlayerTurnGet` -> `MBDPlayerTurnGet`,
`mbMasuTbl` -> `mbdMasuTbl`). Duel-only subsystems: `MBDPartner*`,
`MBDAura*` (hovering aura model used by warps), `MBDEff*`, `MBDCoinScatter*`,
`MBDTelopTitle*` ("1 VS 1 GAME" banner).


### Minigame library (minigame)

Shared helpers used by many minigame overlays. Object kinds and their work
structs: `MgPlayerWork` (player objects in `mgPlayerObjTbl`, created by
`MgPlayerCreate`, updated by `MgPlayerObjMain`), `MgItemWork` (holdable/coin
items in `mgItemObjTbl`, `MgItemObjMain`) and `MgMapWork` (collision map
objects in `mgMapObjTbl`). Map collision shapes set with `MgMapBoxSet`
(box arena bounds), `MgMapCircleSet` (circular arena bounds), `MgMapBlockSet`
(rectangular platform) and `MgMapCylinderSet` (round platform). Other
subsystems: `MgFlow*` (start/finish/result sequence driven by `MinigameFlow`),
`MgGauge*` (segmented power gauges), `MgTime*`/`MgRecord*` (time and best-record
digits), `MgRand*`, `MgStoryStat*` (story-mode status card shown after
minigames), `MgBox*` (opening object with sparkle trail). `MoveOfs` is the
per-frame push displacement accumulated by collisions; `Wall` is a side
collision hit (`mgWallPosTbl`/`mgWallNorTbl`); `Pad` unreferenced gaps in the
main bss are named after the preceding variable (`omobjlastPad`, `...PadB`).

### Minigame overlays (m2DD)

Pattern set by m201-m208. Every minigame overlay uses `m2DD_` (overlay index in
decimal) and the same base names for the same roles:

| Role | Name |
|---|---|
| First function, only calls the setup (absent when the setup itself is first) | `Executor` |
| `omInitObjMan`, cameras, lights, first objects, `MgFlowInit` | `ObjectSetup` |
| `omAddObj` function that initialises and then swaps `obj->func` / the per-frame function | `<Thing>ObjInit` / `<Thing>ObjMain` (empty per-frame stub is still `ObjMain`) |
| Helper that `omAddObj`s one object / one per slot | `<Thing>ObjCreate` / `<Thing>ObjCreateAll` |
| Sequence object (calls `MgFlowMain`, or a hand-written `phase` machine with `GMesCreate` start/finish/winner messages) | `MainObjInit` / `MainObjMain`; its state `phase`, counters `phaseTimer`/`mainTimer`, the play timer `timer` |
| `omSysExitReq` watcher -> wipe wait -> `omOvlReturnEx` | `ExitCheckObjMain` -> `ExitWaitObjMain` -> `ExitObjMain` (a single wait-and-return object is `ExitObjMain`); a bare `omOvlReturnEx(1)` wrapper is `OvlReturn` |
| `CamSetupInit` + scissor/viewport/perspective per camera from a `...Camera` table | `CameraInit` (table `cameraViewTbl`) |
| Fixed `CenterM`/`CRotM`/`CZoomM` start values | `CameraViewInit` |
| Interpolated move between two `MgCameraPreset`s (`cameraMoveObj`) | `CameraMoveStart` / `CameraMoveObjMain` / `CameraMoveTimeSet` |
| The `MinigameFlow` passed to `MgFlowInit` | `mgFlow` |
| `const s16` list passed to `GMesFontMesCreate` | `fontMesTbl` |
| Empty `void (void)` stub between the camera functions | `Dummy` |
| Unreferenced data/bss gap | `<preceding var>Pad` |

Helpers copied verbatim into many overlays (find them with `tools/coddog`):
`AngleAdd` (add and wrap to 0-360), `ObjWorkInit` (clears the overlay's
50-entry `objWorkTbl` of per-slot work: `obj`, timers, sprite `...SprAnim`/`...Spr`
and position fields; field aliases are named after the slot's object),
`PadClear` (zero a player's `HuPad*`), `RandGet` (`rand8() % n`), `RandMulGet`
(`rand8() * n >> 8`), `MotSet` / `MotShiftSet` (motion slot on `model[0]`),
`RotYTurn` / `FrontTurn` (turn `rot.y` toward a target / toward 0),
`GravityCalc`, `PosRotate`, `ScreenPosCalc`/`ScreenXGet` (3D -> 2D), `SprMdlCreate`,
`CameraDebugPad`/`CameraDebugPrint` (D-pad camera editor), `SeDebugPrint`.
Display-list helpers are `Gfx<What><Verb>` (`GfxRectTexInit` = 1-cycle
textured-rectangle mode, `GfxRectXluInit` = translucent prim-modulated mode,
`GfxPrimAlphaSet`); render hooks passed to `Hu3DHookFuncCreate` are
`<Thing>Draw` (`BackDraw` for full-screen background images, `HudDraw` for 2D
overlays).

Players: 1-vs-3 minigames call the group-0 player `Solo` and the others `Team`
unless the game gives them a better role name; each gets `<Role>ObjInit` /
`<Role>ObjMain` / `<Role>ObjCreate`. CPU input is `<Role>ComInput` (writes stick
and buttons, or `HuPad*` directly; `...ComInputCalc` when a wrapper calls it),
`<Role>ComInputGet` when it fills `stickX`/`stickY`/`btn` out-parameters, and the
human counterpart `<Role>PadInput`. Per-player objects created from stubs are
`Player0ObjInit`...`Player3ObjInit` -> `PlayerInit(obj, no)`. Overlays that keep a
`RidiculousRelayPlayer`-style table use `playerTbl` (by player), `groupPlayerTbl`
(by group) and `playerGroupTbl` (group of each player). Character voice tables
(`{2, 3, 7, 4, 5, 6, 8, 9}`) are `voiceChrTbl`; `winner`/`teamChrTbl`/
`teamPlayerNoTbl` hold the result shown by `GMesCreate`.

- m201 Hand, Line and Sinker: `Fisher` (solo angler), `Fish` (team players as
  fish), `Lure` (line end object), `Line` (`FishingLine` display list:
  `LineCreate`/`LineDraw`/`LineKill`, `LinePointsCalc` sag curve solved by
  `LineCurveSolve`), `Eff` splash/wake models, `IntroObjMain`,
  `FisherWinObjMain`/`FishWinObjMain`.
- m202 Coconut Conk: `Solo` rolls on the ground dodging, `Team` ground-pound on
  the ledge to drop `Coconut`s from `Tree`s; `Sea`, `Cloud`, `Back`/`Fore`
  sprites, `SoloFaceSet` (face texture animation).
- m203 Spotlight Swim: `Swimmer` (solo; dives), `Aim` (team spotlight cursors in
  screen space), `Operator` (team models), `Lamp` (spotlights), `Dark` (software
  darkness buffer with light holes), `Bubble`, `Wake`, `Ripple`, `Result` object.
- m204 Boulder Ball: `Pusher` (solo at the top rolling `Boulder`s, MgItem
  objects with hooks), `Runner` (team climbing; `RunnerComInput` hook).
- m205 Crazy Cogs: `Crank` (solo turning the cogs, `crankDir`), `Team`,
  `CogCenter`/`CogA`/`CogB`, `Killer` (Bullet Bills, named from the `SeDebugPrint` text) and `Blast`, `Panel` floor
  shake, `TeamDummy` stand-ins for the intro spin, `comQueueTbl` CPU targets.
- m206 Hide and Sneak: `Seeker` (solo), `Hider` (team; `HiderPath<from>To<to>`
  routes between the four `Spot`s: stump, rock, mushroom house, grass), `Sign`
  (spot signs the seeker picks), `Icon` (2D spot map), `RoundUpdate`.
- m207 Ridiculous Relay: groups 0 (solo) vs 1-3 (team legs: rowing, swimming,
  bicycle); `distTbl`/`speedTbl`/`progressTbl` per group, `relayLegNo`,
  `hurdle`/`shot` obstacles, `BackDraw`/`HudDraw` split-screen 2D layers.
- m208 Thwomp Pull: two sides (`SoloObjInit`/`TeamObjInit` -> `SideInit`,
  `SideObjMain`); `prompt` button order, `hop` Thwomp hops, `rock` thrown at a
  side (`stunTimerTbl`), `dust`, `winJump`, `MotTimeSet`.
- m209 River Raiders: `Boat` (solo player's Red Shell boat; `BoatSteer`,
  engine SE pitch), `Skier` (team players riding Green Shells towed on `Rope`s,
  `skierLaneTbl`, `SkierPushCalc` side bumps), `River` scrolling segments,
  `Water`, `Item` (coins, 5-coin `CoinBag`s and stunning `Log`s: `logCnt`,
  `logHitSe`), `Score` HUD digits.
- m210 Tidal Toss: `Solo` on the bobbing island ground-pounds to start
  `Wave`s (`WaveCreate`, `waveTbl`); `Team` jumps them on the ring; `SeaDraw`
  deforms the sea mesh per wave; `Cloud` sprites; map objects
  `IslandMapObjInit`/`DeepMapObjInit`.
- m211 Eatsa Pizza: two pairs eat a pizza image pixel by pixel (`PizzaEat`,
  `pizzaCntTbl` remaining pixels, `pizzaTileCntTbl` per 32x32 tile for the CPU,
  `PizzaWallHit` uneaten pizza blocks movement), `Crumb` sprites.
- m212 Baby Bowser Broadside: teams on the rotating ring fire `Ball`s from
  `Cannon`s at the moving `KoopaJr` ship (`KoopaJrShake*` when hit); uses the
  shared minigame "system" (see below).
- m213 Pump, Pump and Away: `Pumper`s (players) pump `Pump`s through `Hose`s to
  launch each team's `Rocket`; `Parachute` for the falling rocket, `Smoke`,
  `LaunchEff`, `Lakitu` height signs, `RecordMarker`, sky decorations by
  altitude band (`LowFlyer`/`MidFlyer`/`HighFlyer`/`Cloud`), `Cover` full-screen
  transition, `Seq*ObjMain` chain of sequence steps (`phase`/`phaseStep`).
- m214 Hyper Hydrants: per side a `Pumper` (A/B pumping sets `pumpPowerTbl`) and
  a `Sprayer` (`Spray` particles) put out `Fire`s spawned by a `BigFire`; `Hose`
  segments, `Iris` opening mask, split-screen `CameraViewSet`.
- m215 Picking Panic: split-screen pairs on swings; the catcher (player 0/2)
  grabs items from the dispenser and the thrower (player 1/3) throws them into
  the basket (`itemStateTbl`, `scoreTbl`); `view*Tbl` animate the split.
- m216 Cosmic Coaster: two `Car`s (`Car0ObjInit`/`Car1ObjInit` -> `CarInit`,
  `CarWinObjMain`) with two riders each (`RiderComInputGet`); the `Stage`
  object spawns track objects from `stageSpawnTbl` (`StageItemCreate`): `Rock`/
  `BigRock` obstacles (`...BreakObjMain` when hit), `Coin`s (also light the car,
  `CarLightUpdate`), background `Asteroid`s and the `Goal`; `StageHitCheck`
  lane collisions, `ComTarget*`/`ComLaneMaskGet` CPU lane choice; `Hud`
  (split-screen frame, progress meter, `TrackPosUpdate` scrolling track),
  `StarSky`/`ShootingStar` 2D sprites, `IntroCameraObjMain` keyframe sweep.
- m217 Puddle Paddle: m212-style overlay with the shared `system.c` (collider
  functions are stubs here); teams paddle a `Boat` each (`BoatMoveUpdate`,
  `BoatHitUpdate` picks up items) around the `HammerBro` on the island
  (`HammerBroTurnUpdate`, `HammerBroItemThrow`) that throws `Item`s (type 0
  coin, 1 coin bag, 2 spinning hammer that stuns, `PlayerStunUpdate`;
  `ItemLaunch`/`ItemUpdate`); `Water`, `MdlObjAttach`
  (hand/paddle models hooked onto the character), `TeamComInput` steering.
- m218 Etch 'n' Catch: pairs draw `Line`s (`LineNode*` linked lists per player,
  `lineNodeTbl`) on a byte `grid` sprite (`Grid*`, `gridBuf`) to enclose the
  `Kinopio` on their side; `FillCheck` flood-fills the enclosed region, then a
  `Cage` drops on the caught Toad; `KinopioMark*` animate its marker sprite.
- m219 Log Jam: per team a `Setter` (puts a log on the stump with the matching
  button) and a `Chopper` (`SetterUpdate`/`ChopperUpdate`, `...ComInput`);
  `Log*` pool (`LogCreate`, `LogSplit` into two halves, `LogHalfMove`),
  `Smoke`/`Miss` billboard effects, `Score` tally sprites, `Stage` clouds.
- m220 Slot Synch: each team has two spinning `Block`s (one per player, four
  character faces on the sides: `blockFaceTbl`, `BlockFaceGet` = face in front,
  `BlockSideFaceGet`, `blockSideRotTbl`); a player hits a block to stop it.
  Faces are 0 `Kinopio`, 1 `Kuribo`, 2 `Nokonoko`, 3 `KoopaJr` (4 = no match).
  Matching faces make the character (`Prize`) pop out of the team's `Pipe`
  (`PipeBulgeStart` animates the bulge travelling up the pipe mesh) worth
  `facePointTbl` points (Toad 3, Goomba 1, Koopa Troopa 2, Baby Bowser -1, score
  clamped at 0); `Lamp` sprites show the face sequence, `Score` the team HUD
  (`chrIconSprTbl` player icons), `comFaceTbl` CPU target faces. Shares the m219
  helper library.
- m221 Treadmill Grill: four `Belt` lanes whose speed changes
  (`BeltSpeedChange`, `BeltStop`, `BeltShrink` narrows them); `Fire`s (Podoboo
  model `c201`) wander on the belts and knock players off; `Flame`s ring the
  arena (`FlamePathCalc`); `playerOutTbl` tracks eliminated players.
- m222 Toadstool Titan (later games: Mush Pit): nine Brick `Block`s
  (`BlockObjInit`, `blockObjTbl`, `blockStateTbl`, `blockBreakTimerTbl`) hide
  the Mushroom (`kinoko*` position/velocity, `kinokoPhase`, `kinokoBlockNo`);
  empty blocks break into `debris*` fragments. The player who catches it becomes
  the `giant` (`giantGroup`; `growEff*` transformation; `giantRunF`/`giantRunDir`
  = straight-line run until a wall) and stomps the others out (`outTimerTbl`,
  `outDirTbl`); `ViewFrameSet` screen shake frame.
- m223 Aces High: four `Plane`s in split screen (`Plane*ObjMain` states:
  `Intro`, main, `Return` at the arena edge, `Crash`, `End`); `Shot` bullets
  and homing `Missile`s, `Warn`/`Lock` HUD markers, `Radar`, per-player
  `Camera*ObjMain` modes, `WinViewExpand` grows the winner's viewport.
- m224 Bounce 'n' Trounce: players bounce on springs (`springMdlTbl`,
  `PlayerMotUpdate`) over nine `Tile`s that shake and fall (`TileShakeObjMain`/
  `TileFallObjMain`, `TileNoGet`); Z starts a spin (`SpinEff*` particles,
  `PlayerSpinStop`) that knocks others away (`PlayerKnockBack`,
  `PlayerHitCheck`); `Deco` background models, `PlayerEnd*` dismount at the
  finish, `Dist2DCalc` (x/z float distance).
- m225 Ice Rink Risk: `Puck`s (MgItem copies: `PuckCollide`/`PuckFloorCheck`/
  `PuckShadowSet`/`PuckFloorGet`, `PuckHitReflect`/`PuckWallReflect` bounces)
  knock players out (`PlayerHitHook` -> `PlayerFlyObjMain`); CPU input is
  saved/restored around the MgPlayer hooks (`PlayerComInput`/`PlayerPadRestore`).
- m226 Locked Out: players grab `Key`s (`KeyGrabUpdate`, `keyType` is the
  key that opens this round) and carry them to the `Door`s (`LockedOutDoor`,
  `doorTbl`, `DoorPush`); fewer doors each round (`survivorNum`, `doorNum`).
  Uses the m210/m211 helpers (`CameraViewInit`, `MtxVecMul`, `Rand16Get`,
  `AngleCalc`, `DistXZCalc`, `PlayerWorkGet`, `HookPosGet`, ...).
- m227 Chip Shot Challenge: each `shooterNo` aims (`aimAngle`/`aimPower`,
  `Arc` trajectory guide) and hits the `Ball` toward the hole (`holePos`,
  `BallCupCheck`, `cupInF`); `Lakitu` brings the flag in the intro
  (`IntroUpdate`) and shows the result sign (`CupInLakituUpdate`/
  `MissLakituUpdate`, `DistDisp`); `Confetti*` (mgresultdealer copy).
- m228 Parasol Plummet: players drift down opening/closing their parasols
  (`ParasolOpen`/`ParasolClose`, `PlayerPlummet*`); `Flyer`s throw `Item`s
  (coins, coin bags, spinning obstacles; `ItemThrowProc`) to collect, landing
  on the `Goal`; `Back`/`Side` scrolling sprites, `Cloud` sprites, `Hud`.
- m229 Messy Memory: the room is shown full screen (`room*` slots, `Cover`),
  `Mover`s mess it up (`Dust`), then each player's `Hand` cursor
  (`HandPadInput`/`HandComInput`) puts the `Item`s (`ItemMark` shadows) back
  in their quadrant (`viewOfsTbl`, `viewSpotPosTbl`); `Shutter`s, `Divider`
  split-screen lines, `Score`, `PhaseSet`/`phaseDoneNo` sequencing.
- m230 Picture Imperfect: each face `Part` cycles through variants
  (`PartCycleUpdate`) until the player jumps to hit the block and lock it
  (`PartUpdate`, points popup `PointPopUpdate`); `pictureNo` picks the picture
  set (5/4/3 parts), `sample*` sprites show the target in the intro.
- m231 Mario's Puzzle Party: per-player `field` of columns of `Block`s
  dropped in `Pair`s (`cursorTbl`/`nextTbl`); matches (`Match*`,
  `ChainResolve`) send `garbage` to the others; `BigBlock` squashes columns
  (`SquashProc`); `mode` 0/1/2 (normal/Mini-Game mode/endless with `Timer`/
  `Record`). `SprBatch*` (sprite.c) batches many small textured rectangles
  into one display list (`SprBatchEntryAdd`/`PosSet`/`ScaleSet`/`EntryKill`).
- m232 The Beat Goes On: the `Drummer` plays a sequence (`seqTbl`, `seqLen`,
  `seqNo`) on the A/B/Z drums that the player at the front repeats
  (`DrumHitUpdate`); the `Sheet` HUD shows notes, `Fire` (Podoboo) objects and
  `Smoke` punish misses; `Camera*Move` presets between turns, `Water` scroll.
- m233 MPIQ: quiz (`QuizProc`, `questionNo`, `questionMesTbl`, `choiceTbl`,
  `correctChoiceTbl`, `answerValue`; `QuestionCheck`/`AnswerCalc`/`ChoiceGet`
  build the questions from save data); players jump into their `Block`
  (buzzer, `buzzLockF`, `answerPlayer`) and pick A/B/C (`Choice*`); `Stand`
  pedestals rise and the `Meter` fills per correct answer (`scoreTbl`); wrong
  answers drop the block and `Stun` the player; `Host`, `Logo`, `endlessF`
  debug endless mode.
- m234 Curtain Call: `Actor`s (three character types) march across the stage
  (`ActorMarchUpdate`, `actorTbl`/`actorSlotTbl`/`actorObjTbl`), then the
  `Host` walks out and asks which actor stood at a position
  (`QuestionSet`, `questionTbl`, `answerType`); players rotate their `Sign`
  to a choice (`choiceTbl`), wrong players drop out (`outNum`,
  `survivorTbl`); `Spotlight` reveals the answer; `roundNo`/`roundPhase`.
- m235 Water Whirled: 5-lap boat race on a wavy pool (`WaveHeightGet`,
  `WaterWaveUpdate`); A throttles (`throttleTbl`, engine SE pitch), the stick
  steers (`StickAvgCalc`); `SectionGet`/`LapUpdate` count quarter laps
  (`sectionCntTbl`, `lapTbl`), `RankSpeedUpdate` caps speed by rank
  (`speedMaxTbl`); `Wake` splash models, `Lap`/`Reverse` (wrong way)/`Goal`
  HUD sprites.
- m236 Fridged Bridges: split-screen; each player carries a bridge `Piece`
  from the stock (`PieceGrab`/`PieceDrop`, `pieceStockPosTbl`) to its slot
  (`bridgeSlotPosTbl`) while a jumping `Foe` pushes them into the sea
  (`PlayerFall`/`Freeze`/`Float` obj mains); `Rescue` carries fallen players
  back (`ReturnPosCalc`); `FloorCheck` probes the floor; engine copies keep
  engine names (`ModelMtxGet`, `CameraOutView`, `MapCullFanBatch`).
- m237 Awful Tower: split-screen climb up moving platforms (`platYTbl`,
  `platNoTbl`, `PlatObjInit`) collecting `Coin`s; a `Flyer` throws a `shot`
  at climbers; `BackDraw` renders the scrolling tower strips per view;
  `winner` group zooms its view to full screen.
- m238 Cheep Cheep Chase: m212-style overlay with the shared "system"; players
  swim down the `River` (`Segment`s, `Water` tiles, `Side` decorations),
  jumping `Obstacle` rows, while the giant `Cheep` chases and swallows them
  (`CheepUpdate`, `PlayerSwallowExec`, `ObstacleSwallowExec`);
  `ctrlMode` selects A/B or A/Z controls (`PlayerInputUpdate`/`...B`).
- m239 Pipe Cleaners: split-screen whack game; each player swings at four
  pipe `slotTbl` entries (`PlayerSwingStart`/`PlayerSwingUpdate`) where
  `Target`s rise (`TargetRise`/`Wait`/`Sink`/`Hit`) following a random
  `spawnTbl`; `HitEff`, `Score` digits roll up (`scorePhase`), `RankCalc`/
  `ResultSet`.
- m240 Snowball Summit: players (`SnowballSummitPlayer`, `playerWorkTbl`)
  mash B to make a `Ball` (`PlayerBallMake`, `BallCreate`) and push it, A to
  release it (`PlayerBallRelease`); balls knock others off the summit
  (`BallPlayerHitCheck`, `PlayerFallCheck`/`PlayerFallUpdate`,
  `PlayerKnockUpdate`); `PlayerMoveUpdate` resolves player collisions;
  effects `Puff` (snow trail), `Burst` (ball breaks), `BallMakeEff`, `RollEff`;
  `BackBall`s roll down the background `Mountain`, `Backdrop` side images,
  `Snow` particles; m213-style `Seq*ObjMain` chain (`SeqSettleWaitObjMain`).
- m241 All Fired Up: Podoboo `Fire`s drop in, wander, gather and form
  patterns (`firePhase`, `FirePatternSet`, `patternType`, ring `ringRadius`);
  players dodge, `FireHitCheck` launches them away (`PlayerFlyUpdate`,
  `SmokeUpdate` = m232 copy); `outTimeTbl` ranks by survival time.
- m242 Stacked Deck: players queue (`work[1]` queue slot, `queueLast`) and
  ground-pound one of 12 `Card`s (`PlayerCardFlipCheck`); card types
  `kinoko` (go to the back), `teresa` (shuffle the queue) and `koopa` (out)
  each show a `CardChr`; `deal`/`shuffle` card animations, `HitEff`,
  `Smoke`, swinging `Deco`s; `phaseDoneNo` handshake with `PhaseSet`.
- m243 Three Door Monty: three `Chr`s (Toad, Koopa Troopa, Boo) hide behind
  `Door`s (`ChrShuffleUpdate`, `doorChrTbl`); the `Sign` shows the
  `targetChr`, players answer with A/B/Z (`PlayerAnswerInput`,
  `answerMdlTbl`) and `Digit` sprites show the answer time; `RankCalc`.
- m244 Rockin' Raceway: slot-car race on four `Track`s (`TrackPosCalc`
  bezier nodes); racers alternate A and B/Z (`RacerAccelUpdate`), overheat
  spins out (`RacerGaugeUpdate`, `RacerSpinUpdate`, gauge HUD `Gauge*`);
  flashing `Panel`s boost or spin; `Spark`/`Smoke` effects; photo finish
  `Replay*` (30-frame ring buffer) with `Ghost` images; 3D `Board` shows
  ranks and `Time` digits; `CameraFocus*` keeps racers in view; `SeQueue*`
  delayed sounds. Uses the m219 library plus `BezierCalc`/`BezierVecCalc`/
  `BezierTangentCalc`, `DirRotCalc`, `QuadMdlCreate`.
- m245 Merry-Go-Chomp: players jump onto the `Carousel` seats
  (`PlayerSeatCheck`, `seatFreeTbl`, fewer seats each `roundNo`); it spins
  and stops (`RoundUpdate`, `stopAngleTbl`), and the rider facing the Chain
  Chomp (`Wanwan`, `WanwanChainUpdate`) is bitten (`OutPlayerGet`,
  `BiteEff`); riders return to the queue (`PlayerReturnUpdate`).
- m246 Slapdown: the `Target` shows a symbol, nine spinning `Card`s flip;
  players slap their button when a card matches (`matchF`, `slapOrderNo`),
  wrong slaps are knocked back (`knockVelTbl`, `missCnt`); `Rank` sprites,
  `RankCalc`/`ResultSet`.
- m247 Storm Chasers: players carry a potted Piranha `Plant` (`PlantAttach`,
  hooked on `item_hook`) under the moving rain `Cloud` (`CloudMoveUpdate`,
  `Rain` texture scroll) to water it; `Lightning` strikes (`mark*FrameTbl`
  warning marker) knock players back (`PlayerLightningHitCheck`); at time up
  everyone walks home (`PlayerReturnUpdate`, `goalPosTbl`), throws the plant
  to `plantPosTbl` (`PlantThrow*`, `Puff`) and it grows by rain time
  (`PlantGrow*`); m240-style `Seq*ObjMain` chain and helpers.
- m248 Eye Sore: split-screen; each player runs laps around a Mr. I `Eye`
  (lap count shrinks it, `eyeScaleTbl`; finished eye pops) that knocks back
  players who get too close (`PlayerKnockUpdate`); Podoboo `Fire`s drop in
  (`FireSpawnUpdate`) and stun (`PlayerStunUpdate`, star models);
  `finishRank`/`RankTieResolve`; m245 helper family.
- m249 Vine With Me (duel): players swing on `vine*Tbl` vines (precomputed
  segment x/y/angle per length and frame; `...Base` arrays alias the same data
  offset by four lengths) and press A to jump to the next one
  (`playerStateTbl` 1 swinging / 0 airborne / 2 standing); falling into the
  water shows `Splash` models and respawns; `BackDraw`/`HudDraw` draw the
  scrolling layers and progress icons; `view*` animate the winner's zoom;
  `seqNo`/`seqTimer` sequence.
- m250 Popgun Pick-Off (duel): a 3x3 board of `Target` cards flips up; players
  aim with the stick and fire `Shot`s (`ShotCreate`, `ShotTargetUpdate`); bad
  targets give a `Penalty` (-10). Uses its own `Billboard*` system (sprite
  quads with display lists sorted into opaque/translucent lists:
  `BillboardCreate`/`PosSet`/`PatSet`/`Kill`/`Sort`/`Draw`), unrelated to the
  system.c `Billboard*` models, plus m210/m211 helpers (`MtxVecMul`,
  `ScreenPosCalc`, `WorldPosCalc`, `Rand16Get`, `AnimDataRead`, `SprGrpCreate`).
- m251 End of the Line (duel, split screen): each player rides a cart through
  `Scene`s (`SceneSet`, `sceneReqTbl`: intro drop, track, tunnel, wrong-branch
  `Fall`, `Goal`) choosing left/right at three junctions (`branchRouteTbl`,
  arrow sprites); `TunnelFade`/`BranchFade` sprite fades, `Flare` lens flare,
  per-player `Camera*ObjMain` objects writing `cameraPosTbl`/`cameraAtTbl`.
- m252 Bowser Toss (duel): players spin and throw a Bowser (`Koopa*`,
  `koopaTbl`; `HookMtxBake` bakes the `item_hook` matrices of the spin motion)
  for distance (`ComPowerCalc`, `FallTimeCalc`); `Score` counters for both
  players and the `recordDist`; `Back*` scrolling sky sprites; m219 library.
- m253 Baby Bowser Bonkers (duel): `KoopaJr`s pop out of 14 holes
  (`holePosTbl`) in timed `pattern*Param`/`spawn*Tbl` waves; players hop on
  them (`KoopaJrStompCheck`, `PlayerHopAdd`), squashing them; lava `Stage`;
  CPU `ComTargetGet`/`ComStompTargetGet` by `QuadrantGet`; m219 library.
- m254 Motor Rooter (duel, split screen): players drive along a `Path`
  course (`course0PathTbl`/`course1PathTbl`, `PathPosGet`) steering into one
  of eight directions (`PlayerTurnExec`, `contType`) to avoid `Obstacle`s
  (`ObstacleSafeDirSet`) and collect `Item`s that raise the gear
  (`PlayerGearUpdate`, `gearDecayTimeTbl`); `PlayerCrashExec`; shared system.c.
- m255 Silly Screws (duel): players spin `Nut`s up `Screw`s past `Wall`s
  following the `Sign`/cue models (`PlayerCueUpdate`, `PlayerSpeedUpdate`,
  `NutSpinUpdate`, `StopDistCalc`); shared system.c.
- m256 Crowd Cover (duel): a `Crowd` of 30 billboard characters
  (`crowdTbl`, `CrowdObjMain`; type picked by `stageNo`) covers a picture and
  leaves as the `timer` runs down; players press A/B/Z for one of three
  `choice` sprites (`answerNo`, `missChoiceNo`); m250 `Billboard*` system and
  helpers.
- m257 Tick Tock Hop (duel): players jump the `Clock` hands
  (`ClockObjInit`, `ClockSpeedUpdate`, `ClockObstacleRotUpdate`/
  `ClockPlatformRotUpdate`, `jumpCount` in `gameWork`, `JumpCntUpdate`);
  `PlayerJumpStartUpdate`/`PlayerJumpExec`, `PlayerHitUpdate` (obstacle
  collider), `PlayerKnockExec`, `BothWinExec`/`DrawExec`; shared system.c
  (`ColliderTrackerCreate` links a model position to a quad collider).
- m258 Fowl Play (duel, split screen): players catch the `Chicken`
  (`ChickenObjMain`, `ChickenCatchCheck`; `Feather`/dust billboards,
  `cluckTimer`) inside fenced `wallTbl` segments (`WallPush`,
  `WallCrossCheck`, `WallAvoidCalc`; vector helpers `VecNormalize`,
  `LineParamCalc`, `SegmentDistCalc`, `LineCrossCalc`); per-player
  `CameraObjMain`; m250 `Billboard*` system.
- m259 Winner's Wheel (item): the player hits the `Sign` to start and stop
  the `Pointer` lights around the `Wheel` of six item `Panel`s (one Bowser
  panel, `panelItemTbl`, `panelNo`); `Frame` highlights, `Prize`, `Koopa`
  jumps out on the Bowser panel, two `Npc` spectators; `IntroProc`.
- m260 Hey, Batter, Batter! (item): `Koopa` pitches the ball, the player
  bats it (`swingF`, `ballHitF`, `ballTargetNo`) onto one of five `Base`s
  holding items (`prizeNo`); `Deco` sky models, `Eff` bursts,
  `CameraMoveSet` (sine ease between two camera presets), `EspCreate`,
  `MotMdlRead`; field aliases of `stateWork` in undefined_syms.txt.
- m261 Bobbing Bow-loons (item): the floating player throws a `Dart` at
  five bobbing `Balloon`s (`BalloonHitCheck`, `String`s) that each carry an
  `Item`; a miss pops the player's own balloon (`DartMissProc`,
  `PlayerFallStart`), `Pop`/`Burst` effects, `Koopa` laughs. Object work
  structs are named after their object (`BobbingBowLoonsBalloon`, `...Dart`,
  `...Burst`, `...Pop`, `...Koopa`, `...Item`, `...String`).
- m262 Dorrie Dip (item): the player ground-pounds `Dorrie` so it dips and
  grabs one of six circling `Raft`s (`RaftObjMain`, `grabRaftNo`) holding
  items or `Koopa` (`koopaRaftNo`); `Wake`, `Ripple`, `Burst` effects;
  `TimeUpProc` when the timer runs out. Work structs follow the objects
  (`DorrieDipRaft`, `DorrieDipItem`, `DorrieDipKoopa`, `DorrieDipBurst`,
  `DorrieDipWake`, `DorrieDipStage`, `DorrieDipCom`).
- m263 Swinging with Sharks (item): the player swings on a rope
  (`swingAngle`/`swingPhase`/`swingAmp`, `SwingAngleSet`) and jumps onto one
  of five item `Float`s (`floatTbl`, `hitFloatNo`) while `Shark`s circle on
  spline paths (`SharkProc`, `PathTimeCalc`, `SharkPathMove`); models come
  from the `mdlEntryTbl` list (`MdlEntryCreateAll`, `mdlTbl`/`motTbl`);
  `CameraMoveStart`/`CameraMoveObjMain`, `CameraDebugPad`.
- m264 Swing 'n' Swipe (item): the player swings a bat at five `Carrier`s
  running around with item `Box`es (`CarrierEnter`/`Run`/`Flee`/`Gather`
  updates, `hitCarrierNo`); `stickHistTbl` averages stick input;
  m260 helpers (`EspCreate`, `MotMdlRead`, `Exit*ObjMain`); field aliases of
  `carrierWork` in undefined_syms.txt.
- m265 Stardust Battle (story finale): the player fights the Millennium
  `Star` (`StarObjMain` state machine, `starWork`, HP `starHpMax`/
  `stageHpTbl` thresholds that switch the `Stage`) by grabbing fallen `Dust`
  stars (`DustDrop` onto shuffled `DropSpot`s, `DustGrab`/`DustThrow`/
  `DustHitCheck`, `PlayerDustHoldUpdate`) and throwing them back; three stages
  `Ground`/`Wave` (vertex `WavePoint`s pushed by `Ripple`s)/`Comet` (mirror
  floor, `PlayerComet*` reflection model) each with `PlayerStage*Tbl` hooks;
  `Ray`s + `RayBurstStart` on defeat (`StarDefeatStart`), `Time` digits with a
  record row (`recordF`), m219 library (`Smoke*`, `EffMdl*`, `Camera*`).
- m266 Game Guy's Roulette: the player picks a `Prize` section
  (`prizeMulTbl`, `PrizeSelectUpdate`) and Game Guy (`Gamble`) spins the
  `Ball` around the `Wheel` (`SpinUpdate`, `winSlotNo`/`winPrizeNo` decided up
  front by `WheelInit`); `Marker` shows the choice.
- m267 Game Guy's Lucky 7: Game Guy and the player take turns hitting a dice
  block (`Sai`, `SaiNum`, `saiNo`) to climb seven steps (`gambleStep`/
  `playerStep`, `...StepPosTbl`, `Gamble`/`PlayerChoiceProc` = roll again?);
  8 or more is a bust (`...BustObjMain`, `BustEff`), 7 pays 10 coins with
  `Confetti`.
- m268 Game Guy's Magic Boxes: two boxes hide Toad (`Kinopio`) and Baby Bowser
  (`KoopaJr`); per round (`roundNo`, three `roundLampSprTbl` lamps) the boxes
  drop (`BoxDropUpdate`), shuffle behind the `Curtain` (`ShuffleUpdate`), the
  player picks one (`BoxSelectUpdate`, `kinopioSideTbl`) and may continue
  (`ContinueProc`, coins double); `BoxSpot*` is a second software spotlight
  layer.
- m269 Game Guy's Sweet Surprise: the player bets on which of two Chain Chomps
  (`WanwanL`/`WanwanR`) finishes its `Cake` first (`EatObjMain`, `eatCntTbl`,
  `oddsTbl`/`oddsNum`, `sidePayoutTbl`); `Marker` token, `Bell`, `Crumb`
  effects.
- m270 Dizzy Dinghies (story): solo boat race to the `GoalCheck` plane on one
  of three courses (`courseNo`, `course<n>Obstacle{Pos,Rot,Type}Tbl`,
  `ObstacleDispUpdate`); `Lakitu` start signal; m235 copies keep m235 names
  (`WaveHeightGet`, `WaterWaveUpdate`, `NormalCalc`, `PlayerTiltUpdate`,
  `PushClamp`, `PlayerCollide`, `StickAvgCalc`, `MoveAvgCalc`, `WakeUpdate`).

Game Guy minigames (m266-m269): Game Guy is `Gamble`; each has its own copy of
`intro.c`, the software-drawn spotlight intro (`SpotIntroInit`/
`SpotIntroUpdate`, `SpotBeamInit`/`SpotBeamUpdate` = light beam on the result,
`SpotLayerInit`/`SpotLayerClear`, `SpotDraw`/`SpotDrawEx`/`SpotErase`/
`SpotLineDraw` into `spotColorLayer`/`spotMaskLayer` buffers, `spotBufNo`).
Shared helpers: `Rand` (16-bit `rand8` pair scaled, copy of `MBRand`),
`PlayerInfoInit` (`playerInfo`: player, pad, chr, CPU flag, difficulty,
coins), `RuleProc` (rules window), `WinCreate`/`WinKeyWait`/`WinChoiceGet`/
`WinClose`, `comKeyWaitTbl`/`comLevel`, `EspSlotCreate`/`SprParamSet`/
`SprDispSet` (esprite parameter blocks), `HudObjInit`/`HudObjMain`,
`BannerUpdate` (blinking title banner), `chrNameTbl` (lose message),
`ExitStartObjMain` -> `ExitObjMain`, `ExitCheckObjMain`.

Item minigames (m259-m264) drive their sequence from `MainObjMain` (calling
`MgFlowMain`, or a `phase` switch with `IntroObjMain`/`PlayObjMain`/
`ResultObjMain`) and run one-shot animations as `<Thing><Action>Start` (adds
the process) + `<Thing><Action>Proc` (the `omAddPrcObj` body); the 10-second
countdown process is `TimerProc`; `playerNo` is the group-0 player and
`bonusCoin` gets the won item (`-1` for Bowser / nothing).

Helpers copied into m242, m243, m245, m246 (and others in this family):
`MotShiftSet`/`MotSet` that track the current motion through an `s16 *`,
`VelCalc` (per-axis step toward a point), `RotVelCalc` (velocity from `rot.y`
quadrant), `AngleTurnCalc`, `CameraDebugPrint` (prints zoom/rot between two
points), `CameraViewInit`. Grouped BSS that the code also reaches through
field aliases is named after its role (`m242_phaseWork`, `m246_stateWork`).

Shared "system" helpers (m212, m254, m255, m257 and other overlays with a
`system.c`): `SystemCreate`, `FuncGroupCreate`/`FuncSet`/`FuncReset`/
`FuncTagReset`/`FuncGroupReset`/`FuncGroupUpdate`/`FuncGroupSort` (prioritised
callbacks per object), `SprCreate`/`SprDispOn`/`SprDispOff`/`SprUpdate`,
`AnimMdlCreate`/`AnimMdlLinkCreate`/`AnimMdlFreeGet`/`AnimMdlDispOn`/`AnimMdlUpdate`,
`Billboard*` (sprite-textured billboard models), `Collider*` + `Mover*`
(plane/cylinder/sphere/prism hit checks), `LerpCalc`, `BezierCalc`,
`RandPermCreate`, `MdlSync`, `PitchYawCalc`, `AngleDiffMinimize`, `Mtx*Set`/
`MtxMul`/`VtxTransform`, `MtxTransCalc`; data `sprTbl`, `animMdlTbl`,
`funcGroupTbl`, `gameWork`, `playerTbl`, `playerNoTbl`. Per-object
`FuncContext` callbacks are named `<Thing>Update` (per frame) or `<Thing>Exec`
(sequence), e.g. `CameraFollowUpdate`, `StartExec`, `PlayerJumpExec`. m254,
m255 and m257 all use these noun-then-verb names (m257's earlier verb-first
names such as `CalcLerp`/`UpdateFuncGroup` were converted).

Other copied helpers named here: `MtxVecMul`/`MtxInvert`/`ScreenPosCalc`/
`WorldPosCalc` with `CameraViewInit` caching the camera matrices (m210, m211),
`PlayerCreate` (copy of `MgPlayerCreate`), `PlayerWorkGet` (data + `unk158`),
`Rand16Get` (LCG with `randSeed`), `AnimDataRead`/`SprGrpCreate`/
`SprAnimPatGet`/`SprPatDataGet`, `DistXZCalc`, `AngleCalc`, `PhaseSet`,
`ArcTanCalc`/`PolarCalc`, `TextPrint`, `SePanPlay`, `MdlAnimTimeSet`.

Battle/2-vs-2 helper library first named in m219 (Log Jam) and shared by m220
Slot Synch, Rockin' Raceway, Stardust Battle, Bowser Toss and Baby Bowser
Bonkers: `ExitCheck`/`ExitObjMain` (exit request watcher with its own
`exitTimer`), `WorkPtrSet`/`WorkPtrGet` (pointer packed into `work[0..3]`),
`SprAnimRead` (DataRead + HuSprAnimRead), `SmokeInit`/`SmokeObjMain`/
`SmokeCreate` (8-slot billboard effect pool; a second pool with the same code
gets an overlay-specific name), `CameraInit`, `CameraDebugPad` (with
`cameraDebugMode`/`cameraDebugX`/`cameraDebugY`), `CameraKeyStore`,
`CameraMoveStart`/`CameraMoveObjMain` (`cameraKeyTbl`, `cameraMoveTimer`,
`cameraMoveTime`, `cameraMoveF`), `CameraPosUpdate`, `AngleDiffCalc`,
`AngleStepCalc`, `InterpCalc` (linear), `AngleInterpCalc`, `StepCalc`,
`MotSet`/`MotShiftSet`/`MotShiftTimeSet`/`MotShiftUpdate`/`MotStop`,
`EffMdlUpdate`, `NodeMtxCalc`/`NodeWorldMtxCalc` (bake one node's matrix),
`BillboardColorMdlCreate`/`BillboardColorMdlLink`/`BillboardColorPatSet`/
`BillboardVtxCreate`, `MotCreate`; data `flag10F` (`_CheckFlag(10)`),
`frameCnt`, `phase`/`phaseTimer`/`timer`, `resultWait`, `teamTbl`,
`playerWorkTbl`, `teamPlayerAltTbl`, `winAnimTbl`/`loseAnimTbl`,
`voiceChrTbl`/`voiceNoTbl`, `chipColor`/`whiteColor`, `gfx*Init` display lists.

### Party board overlays (wNN)

Pattern set by w01 (Chilly Waters); w02-w06, w10 and the duel boards (with
`MBD<n>_`/`mbd<n>_`) should reuse the same base names. Functions are
`MB<n>_` for board setup and CPU helpers and `MB<n>Ev_` for anything run from
a space event, item hook or star/map sequence. Data follows its user:
`mb<n>ev_` for event data, `mb<n>_` for board-level data and CPU (`Com`) data.
Event tables are always `mb<n>_...EventTbl`.

| Role | Name |
|---|---|
| `OvlEntrypoint` table / entry stub | `mb<n>_ovlEntryTbl`, `MB<n>_Executor` |
| Entries 0-4 | `MB<n>_BoardInit`, `MB<n>_SaveInit`, `MB<n>_Create`, `MB<n>_BoardReload`, `MB<n>Ev_OpStarMapView` |
| Shared setup called by Create/Reload | `MB<n>_ObjectSetup` |
| `event_table_entry[]` passed to `MBMasuEventTblAdd` | `mb<n>_commonEventTbl` (star/bank/shop/gates), `mb<n>_specialEventTbl` (branches, merges, board gimmicks), `mb<n>_teresaEventTbl`, `mb<n>_turnStatusEventTbl` |
| `event_list_entry[]` for one space | `mb<n>_<Handler>EventTbl` (`mb1_branch5EventTbl`, `mb1_starMasuEventTbl`, `mb1_merge3EventTbl`) |
| Junction with a choice (`MB<n>Ev_BranchMain`) | `MB<n>Ev_Branch<k>` numbered in `specialEventTbl` order; its arguments `mb<n>ev_branch<k>Masu`, `mb<n>ev_branch<k>Link`, `mb<n>ev_branch<k>ComTree` (elements `...ComTree0..2`, nested star-position sub-trees `...ComTree0Star5`) |
| Junction handler that only runs while a Reverse Mushroom is active (`rev & 0x80`) | `MB<n>Ev_Branch<k>RKinoko` |
| One-way path join (`MB<n>Ev_BranchMerge` / `MBMoveNextMasuSet` only) | `MB<n>Ev_Merge<k>` |
| Branch handler run after a space event | `MB<n>Ev_<Masu>MasuBranch` (`MB1Ev_StarMasuBranch`) |
| Star spaces | `MB<n>Ev_Star*` (existing), `mb<n>ev_starFlag`, `mb<n>ev_starMasu`, `mb<n>ev_starGuideMasu` |
| Guide models (Toad at star spaces, Boo) | `MB<n>_StarGuideCreate[All]`, `MB<n>_TeresaGuideCreate[All]`, `mb<n>_starGuideMdl`, `mb<n>_starGuideBaseMdl` |
| Bank / shop / Boo spaces | `MB<n>Ev_BankMasu`, `MB<n>Ev_ShopMasu`, `MB<n>Ev_Teresa`; data `mb<n>ev_bank*`, `mb<n>ev_shop*`, `mb<n>ev_teresa*`; bank coin piles `MB<n>_BankCoin*` |
| Map-screen icons | `MB<n>_<Thing>MapIconAddAll`, `mb<n>_<thing>MapIconMasuTbl`, `...MapIconOfsTbl` (icon 8 = bank, 9 = shop, 0xA = Boo, 0xB = star guide, 0xC = gate) |
| Skeleton-key gates | `MB<n>_Gate*`, `mb<n>_gate*`, space handler `MB<n>Ev_KeyManMasu` |
| CPU choice helpers | `MB<n>_Com<Thing>Choice` (drives the window), `MB<n>_Com<Thing>Decide` (computes the answer), `mb<n>_com<Thing>Target` |
| CPU item trees used by `MB<n>_ComItemDecide` | `mb<n>_item<Item>ComTree` (`mb1_itemSKinokoComTree`), per-star sub-trees `mb<n>_item<Item>Star<i>ComTree` (`Star06` = mask of stars 0 and 6) |
| Yes/no trees passed to `MB<n>Ev_YesNoChoiceGet` | `mb<n>ev_<event>ComTree` |
| Motion lists passed to `MBModelCreate` | `mb<n>[ev]_<thing>Mot` (`mb1_gateMot1`, `mb1ev_shopKinopioMot`) |

Board-gimmick terms: `Turuturu` (slippery ice slide), `Snowman`, `Lake`/`IceCrack`
(w01 ice breaking), `KinokoMark` (mushroom status model orbiting a player),
`TereYoke` (Boo Repellent), `KoopaCard` (Koopa Kard), `After5` (Wacky Watch),
`LampSmoke` (Magic/Lucky Lamp particles).

More shared board roles (from w02):

| Role | Name |
|---|---|
| `?` space hook passed to `MBHatenaFuncSet` (when it just dispatches) | `MB<n>Ev_Hatena` |
| Junction handler with extra direction logic around the branch | `MB<n>Ev_Branch<k>Check` |
| Window choice helper used only by the key-gate space | `MB<n>Ev_KeyManChoiceGet` |
| Shared `{1, 2, 4, 8}` rodata (window player mask by pad) | `mb<n>_padBitTbl` |
| Per-character tables | suffix `Mario`, `Luigi`, `Peach`, `Yoshi`, `Wario`, `Dk`, `Waluigi`, `Daisy` (character order) |
| Com sub-trees reached from another tree | parent name plus a suffix for the referencing node type: `Star<i...>` (type 2), `Sub` (0), `Coin` (1), `Walk` (3), `Flag` (4), `Rank` (5), `Func` (6), `Item` (8), `WalkMin` (9), `Pos` (10), `LowCoin` (12), `Chr` (13), `OtherCoin` (16). A sub-tree shared by several `...ComTree<e>` of one branch drops the element index (`mb2ev_branch4Star5ComTree`) |
| Per-star CPU target trees for mushrooms | `mb<n>_item<Item>SelfComTree` (current player), `mb<n>_item<Item>TargetComTree` (other players), elements `...Star<i>ComTree` |

w02 (Deep Bloober Sea) gimmick terms: `Vacuum` (happening at the suction pipe:
`VacuumRoulette` arrow, `VacuumEff` particles, `MB2Ev_ActionTimeTitle*` sprite; players mash
A to resist), `HatenaWarp` (other `?` spaces carry the player to a paired space,
`mb2ev_hatenaWarpMasuTbl`), `Shortcut` (guess-one-of-four event on space 125;
`ShortcutMark` models show already-picked choices, a correct guess carries the
player across).

w03 (Spiny Desert) gimmick terms: `Mirage` (a second, fake star space chosen
each shuffle; `MB3_ComMirageCheck` is a CPU tree callback that flags players
whose path reaches the mirage before the real star, `mb3_comMirageOrder<k>Tbl`
are per-junction star visit orders), `Quicksand` (the `?` space hook opens a
quicksand pit that swallows nearby players and spits them out at another pit;
`MB3Ev_QuicksandSinkProc`, `...StruggleProc`, `...ExitProc`), `SandPit` (the two
small pits on the shortcut at space 114: `MB3Ev_SandPitBranch` offers the route,
`MB3Ev_SandPitJump` makes the player time A-presses to jump each pit, falling in
drops them elsewhere). Rev-only junctions that pick an arrow list by the space
the player came from name those lists `...From<masu>Masu` (decimal space id),
as in w01 (`mb3ev_branch13RKinokoFrom98Masu`). A branch `ComTree` array shared
by two junctions takes the first junction's number (`mb3ev_branch9ComTree` is
used by branches 9 and 10).

w04 (Woody Woods) gimmick terms: `Arrow` (the three direction signs at
spaces 121-123 whose state lives in `boardData.halfWordBytes[0..2]` and decides
junctions 3, 5 and 7; `MB4_ArrowCreate[All]`, `MB4_ArrowDirUpdate` re-aims the
models, `MB4Ev_ArrowFlipExec` swings the hammer and turns one or all signs;
`MB4Ev_ArrowPay` is the pass-space event that flips all signs for 5 coins, with
per-space trees `mb4ev_arrowPayMasu115ComTree`/`...Masu104ComTree`;
`MB4Ev_ArrowRoundFlip` flips them at round start (event id -2);
`MB4Ev_HatenaArrowFlip` flips one from a `?` space), `Pick` (`?` space event
where the player picks one of two falling boxes; a correct pick lets them roll
again, `MB4Ev_HatenaPickRev` is the variant that rolls backwards; signs
`mb4ev_pickSignMdl`, title sprite `MB4Ev_ActionTimeTitleProc`). A pass-through handler that sets both next and back spaces
counts as a branch (`MB4Ev_Branch1`, as `MB2Ev_Branch1`); its reverse-direction
companion keeps `...Rev` (`MB4Ev_Branch1Rev`, as in w01).

w05 (Creepy Cavern) gimmick terms: `Whomp` (the Whomp at space 98 that blocks one
of two routes; `boardData.halfWordBytes[0]` is its side, `[1]` the item it asks
for (Skeleton Key / Mushroom / Poison Mushroom), re-rolled by
`MB5_WhompItemShuffle`. `MB5Ev_WhompExec` asks the player for the item and swaps
the Whomp's side; `MB5_WhompProc` drives the model (`mb5_whompMot`) when
`mb5_whompMoveF` is set, `MB5_WhompRockProc` drops rocks; per-space yes/no trees
`mb5ev_whompMasu<masu>ComTree`; `MB5_ComWhompItemCheck` is the CPU tree callback;
`MB5Ev_WhompMasu<masu>Check` are the space handlers that only call it).
`Cart` (mine cart on the two rails whose block positions live in
`halfWordBytes[3]`/`[4]`: `MB5Ev_CartRide[Exec]` is the pay-5-coins ride on
spaces 112/150 where the player times an A press (`MB5Ev_CartJumpProc`, shown with
the shared `ActionTimeSpr` sprite, state in `mb5ev_cartJumpStateTbl`) to jump into
the passing cart; `MB5Ev_CartRunExec` is the `?` space version that just sends a
cart through (`MB5Ev_HatenaCartA`/`B`); players on the track are moved aside by
`MB5Ev_CartPlayerEscape*`. `CartBlock` is the stopper model at either end of a
rail (`mb5_cartBlockMdlA`/`B`) that the cart pushes to the other end).
Merge handlers that also start a gimmick are named after it
(`MB5Ev_CartRideMerge1`); `MB5Ev_BranchRKinokoMain` is a shared Reverse-Mushroom-only
wrapper around `MB5Ev_BranchMain`. Per-space tables selected by the current
space use `Masu<id>` (`mb5ev_cartBranchMasu126Tbl`, `mb5ev_cartRideMasu150ComTree`).

w06 (Waluigi's Island) gimmick terms: `Roulette` (the spinning arrow on space 153
reached from junction 2 (`MB6Ev_Branch2`): `MB6Ev_RouletteArrowProc` cycles the
arrow over four directions, `MB6Ev_RouletteExec` has the player press A to jump
on and stop it (`mb6ev_rouletteDir` while spinning, `mb6ev_rouletteStopDir` once
stopped; the stopped direction picks `mb6ev_rouletteLinkTbl`/`...LinkIdxTbl`);
the "Action Time" sprite proc is `MB6Ev_ActionTimeTitleProc`; CPU trees `mb6ev_rouletteDir1ComTree`/`...Dir3ComTree`
pick the direction to aim for). `Bomb` (the countdown model on space 148: the
counter in `boardData.halfWordBytes[1]` is shown through an anim bank,
`MB6_BombCountUpdate`; `MB6Ev_BombCountExec` is the `?` space event that lowers
it and, at zero, explodes and takes all coins from players on
`mb6ev_bombMasuTbl`). `Bridge` (the two bridge models on spaces 117/112; the
active one is `halfWordBytes[0]` and decides junctions 6, 7, 12 and 13;
`MB6Ev_BridgeSwapExec` is the `?` space event that swaps them). `Hole` (the
three holes at spaces 133/120/135 that the passing event `MB6Ev_HoleEnter` on
spaces 132/118/134 drops players into; they come out of `mb6_holeExitMdl` on
space 139 and continue with the Reverse-Mushroom junction
`MB6Ev_HoleExitBranch`). `Trapdoor` (pass event on spaces 124/125 with a 50%
chance of dropping the player to the hole exit, `MB6Ev_Trapdoor`).
`ChangeMasu` (spaces in `mb6_changeMasuTbl` whose type is re-rolled from
`mb6_changeMasuTypeTbl`: `MB6Ev_ChangeMasuTypeRoll` picks, event id -3;
`MB6Ev_ChangeMasuTypeSet` applies, event id -2).

`ActionTimeTitle` is the flipping "Action Time" title sprite shown on its own
(`MB<n>Ev_ActionTimeTitleProc` / `...Create`, w02, w04, w06);
`ActionTimeSpr` is the version that also shows a per-player result box
(`MB1Ev_ActionTimeSpr`, w03, w05, w10).

w10 (tutorial board): board setup, the guide/bank models, the camera follower
and the pause/quit process use `MB10_`/`mb10_`; the scripted lesson
(`MB10Ev_TutorialProc`) and every helper it calls use `MB10Ev_`/`mb10ev_`.
Lesson helpers: `MB10Ev_GuideWin*` (guide speech window: `Exec` = open, wait
key, close), `MB10Ev_Caption*` (lesson caption sprites), `MB10Ev_Icon*`, demo
procs reusing shared-board terms (`ItemMasuKinopioProc`, `BattleKuriboProc`,
`GambleProc`, `ShopProc`, `KakusiExec`), and `Cart` (Action Time demo where
players run to a cart, `MB10Ev_CartJumpProc`, `mb10ev_cartJumpStateTbl`).

### Duel board overlays (duelNN)

Pattern set by duel01 (Gate Guy); duel02-06 and duel10 should reuse the same
base names with `MBD<n>_`/`MBD<n>Ev_`/`mbd<n>_`/`mbd<n>ev_`. Board setup
mirrors the party boards (`MBD<n>_Executor`, `mbd<n>_ovlEntryTbl`,
`MBD<n>_BoardInit`/`SaveInit`/`Create`/`BoardReload`, `MBD<n>_ObjectSetup`,
`MBD<n>_MapScroll`, `MBD<n>_BranchHelpStart`/`End`, `mbd<n>_commonEventTbl`,
`mbd<n>_specialEventTbl`, `MBD<n>Ev_Merge<k>`, `MBD<n>_Gate*`).

| Role | Name |
|---|---|
| Per-partner attack sequences passed to `MBDPartnerAttackFuncSet` (index = `PARTNERS` enum) | `MBD<n>_<Partner>AttackExec` (`Nokonoko`, `Kuribo`, `Kinopio`, `Bomhei`, `Teresa`, `Whomp`, `Snifit`, `Pakkun`, `Wanwan`, `Dossun`, `Blizzard`, `KoopaJr`); Boo's counter variant `MBD<n>_TeresaCounterExec`; the setter `MBD<n>_PartnerAttackInit` |
| Attack helpers | `MBD<n>_AttackTargetPosGet`, `MBD<n>_AttackCameraFocusSet`, `...CameraSpeedMoveCreate` / `...CameraTimeMoveCreate`, `MBD<n>_AttackEffMdlCreate` / `...DispOn`, `MBD<n>_Dodge{Proc,Create}` (target sidesteps, `flags & 8`), `MBD<n>_MissMark{Proc,Create}` (bouncing mark sprite), `MBD<n>_CameraShake{Proc,Create}`, `MBD<n>_BomheiMdlSwap`, Baby Bowser's `MBD<n>_KoopaJrChange[End]Exec` and `MBD<n>_KoopaFire*` breath particles |
| Walk-past attack hook passed to `MBDWalkAttackHookSet` | `MBD<n>_WalkAttackHook` |
| `?` space hook passed to `MBDHatenaFuncSet` / its outcome table | `MBD<n>Ev_Hatena`, `mbd<n>ev_hatenaFuncTbl`, outcomes `MBD<n>Ev_Hatena<Thing>` (`HpRecover`, `PosSwap`, `CoinLose10`, `CoinGain10`/`20`, `StartWarp`, `MasuOwnerSwap`/`Clear`, `PartnerPowerUp`/`Down`, `PartnerSwap`) |
| Each player's start space (pay wages, roulette for a new partner) | `MBD<n>Ev_StartMasu1P`/`2P` -> `MBD<n>Ev_PartnerGetExec`; roulette `MBD<n>Ev_PartnerRoulette{Exec,Proc}`; CPU choices `MBD<n>_ComPartner*` with per-character tables `mbd<n>_comPartner<Chr>Tbl` |
| Turn start (`-5` event, partner wages, Snifit coin gift) | `MBD<n>Ev_TurnStart`, `mbd<n>_turnStartEventTbl` |

Player-specific variants use `1P`/`2P` (player index 0/1, as in the game's
own strings). Duel CPU tree node types differ from party boards; sub-tree
suffixes: `Lv<k>` (type 22, CPU difficulty k), `Player` (21, current player
index), `WalkMin` (7), `OtherPos` (11, opponent position range), `Func` (5);
tree callbacks are `MBD<n>_Com<Tree>Check` named after the sub-tree that
uses them (`MBD1_ComGate1PayLv2OtherPosCheck`).

duel01 (Gate Guy) terms: `GateGuy` (the bell-counter model on space 29;
`GwSystem.bank_coins` counts down the bells, at zero the opponent is warped in,
`MBD1Ev_GateGuyWarpExec`, and a minigame starts; `MBD1Ev_GateGuyMasu`),
`Gate<k>Pay` (pay 5 coins to open a gate onto route 3, `MBD1Ev_Gate1Pay`,
`mbd1ev_gate1PayComTree`), `Route3Start`/`End` (route 3 entry/exit handlers,
named from their debug strings), `PartnerBox<k>` (the model each player hits
to get a partner; `SwayProc`, `SquashProc`).

Every duel board has the Gate Guy, partner boxes, `MBD<n>Ev_GateGuyWarpExec`,
`MBD<n>Ev_GateGuyMasuBranch` (the type-8 entry of `mbd<n>_gateGuyMasuEventTbl`,
empty on boards without a reverse choice) and `MBD<n>Ev_StartWarpLinkGet`, so
those names apply on every board. Branch spaces that open a branch-arrow
choice are `MBD<n>Ev_Branch<k>` (numbered in `mbd<n>_specialEventTbl` order)
with `mbd<n>ev_branch<k>Masu` (link list), `mbd<n>_branch<k>EventTbl` and
`mbd<n>ev_branch<k>ComTree`; link-only handlers are `MBD<n>Ev_Merge<k>`.
`Lv<k>Player` sub-trees can contain two `WalkMin` nodes (`...WalkMin2ComTree`).
Tables of the opponent's link index reached after N steps, used by
`MBD<n>_ComBranch*Check`, are `mbd<n>_comLink<k>IdxTbl` (or one 2D
`mbd<n>_comLinkIdxTbl`).

duel02 (Arrowhead) terms: `Arrow` (the two arrow-sign models on spaces 37/39,
`MBD2_ArrowCreate[All]`, `mbd2_arrowMdl`; `MBD2_ArrowMotion{Proc,Create,Reset}`
plays/resets the sign's motion when a player passes the merge spaces in
reverse).

duel03 (Pipesqueak) terms: `Pipe` (the four warp-pipe models,
`MBD3_PipeCreate[All]`, `mbd3_pipeMdl`); `MBD3Ev_PipeWarpExec` sends the player
and partners down a pipe and out of a random other one
(`mbd3ev_pipeWarpMasuTbl` -> `mbd3ev_pipeExitMasuTbl`), called when the player
accepts at `MBD3Ev_Branch<k>`.

duel04 (Blowhard) terms: `Blowhard` (the whirlwind model on the Gate Guy
space 32, `mbd4_blowhardMdl`, with its face anim `mbd4_blowhardAnim` /
`mbd4_blowhardAnimData`; `MBD4_BlowhardCreate`/`Init`/`Close`,
`MBD4_BlowhardSpinStart`/`Stop`). `MBD4Ev_BlowhardExec` is the walk-end hook
(`MBDWalkEndHookSet`): `MBD4Ev_BlowhardSpinExec` spins the player and swaps
their partners, then `MBD4Ev_BlowhardBranch` offers the three exits other
than the way the player came (`MBD4Ev_BlowhardStraightSet` just continues
straight through). Junctions whose arrow list depends on the space the player
came from use `From<masu>` throughout: `mbd4ev_branch1From20Masu`,
`mbd4ev_branch1From20ComTree`, `MBD4_ComBranch1From20Lv3Check` (the default
case is named after the remaining origin space). When a choice runs a second
or third CPU tree to decide whether to skip more arrows, those trees take
`Sel2`/`Sel3` (`mbd4ev_blowhardBranchFrom19Sel2ComTree`,
`mbd4ev_gateGuyBranchSel3ComTree`). Per-link CPU index tables walked in the
opposite direction add `Rev` (`mbd4_comLink0RevIdxTbl`).

duel05 (Mr. Mover) terms: `Conveyor` (the conveyor belt on space 39 whose
direction flips every turn: `MBD5_ConveyorCreate` picks the model from
`mbd5_conveyorMdlTbl` by turn parity, `MBD5_ConveyorScrollObjMain` scrolls its
texture, `MBD5Ev_ConveyorRoundFlip` (event id -2) rebuilds it each round).
`MBD5Ev_ConveyorRide` moves the player along it; `MBD5Ev_ConveyorEnterA`/`B`
and `MBD5Ev_ConveyorRouteASet`/`BSet` record in
`boardData.halfWordBytes[player]` which side (A = space 21, B = space 3) the
player came from, used by `MBD5Ev_ConveyorRevExit`/`ConveyorRevMerge` when
walking backwards; `MBD5Ev_ConveyorMerge` points the player at the belt in its
current direction. Link-only handlers are numbered `MBD5Ev_Merge<k>` in
`mbd5_specialEventTbl` order. Duel CPU index tables are named after the link
they cover (`mbd5_comLink<link>IdxTbl`).

duel06 (Backtrack) terms: `Switch` (the five linked switch models on spaces
31/25/24/33/32, `MBD6_SwitchCreate[All]`, `mbd6_switchMdlTbl`,
`mbd6_switchMasuTbl`; `boardData.halfWordBytes[0]` is the loop direction).
`MBD6Ev_SwitchMasu` is the event on the spaces in `mbd6ev_switchEventMasuTbl`:
the player walks to the switch, `MBD6Ev_SwitchPressExec` animates it, the
direction flips and `MBD6Ev_PlayerDirFlip` swaps both players' next/back links
and `rev`.

duel10 (tutorial board) mirrors w10: `MBD10_PauseProc`/`PauseQuitCheck`
(`mbd10_pauseOnF` = START may pause), the scripted lesson
`MBD10Ev_TutorialProc` and its helpers (`MBD10Ev_GuideWin*`, `GuideJump`,
`GuideMove`, `GuideMotProc`, `Caption*`, `SaiExec`, `TelopExec`, `TurnNext`,
`PlayerWalkExec`, `MasuCoinExec`) use the w10 base names with `MBD10Ev_`.
Duel-only helpers: `MBD10Ev_PlayerWalkExecEx` (walk with a step limit),
`MBD10Ev_SaiStart`/`SaiWait` (dice hit split in two), `MBD10Ev_PlayerRevOn`/`Off`,
`MBD10Ev_PartnerAppearExec`/`VanishExec`/`PuffEffCreate` (partner swap with smoke
puffs), `MBD10Ev_SnifitCoinGiftExec`, `MBD10Ev_Hatena`/`HatenaEnd` (the `?`
title sprite split around the minigame roulette). `MBD10Ev_ComSetAll` and
`MBD10Ev_PlayerColorReset` are empty stubs in the slots where w10 calls them.

### Board intro overlays (opboard, opboardtutorial)

`opboard_`/`opboardtutorial_` share base names: `ArriveProc`/`ArriveExec`
(players land on the platform and warp), `TurnOrderExec` (dice for turn order),
`StarTalkExec` / `GuideTalkExec` (host speech), `SpiralEffCreate`/`Add`/`Hook`
(spiral particle model; `Hook` is the particle update callback), `Path*`
(spline path through a `9999.0f`-terminated point list), `SysInit`/`SysClose`
and `BackInit`/`BackClose` (board library and background setup/teardown),
`ExitCheckObjMain`/`ExitObjMain`, `centerMdl` (platform, later the star host).

The duel intros `opduel_`/`opdueltutorial_` reuse those base names (`ArriveProc`
in opduel, `ArriveExec` in the tutorial, as in the party intros).
`StarTalkExec` is the whole host sequence including turn order and the
starting-partner choice; `partnerMdlTbl`, `partnerMot<Chr>`, and
`partnerStartPosTbl`/`partnerPosTbl`/`partnerSlotPosTbl` are the starting
partners. Player positions: `playerStartPosTbl` (on the platform),
`playerPosTbl` (arrival), `playerFarPosTbl`/`playerNearPosTbl`/`playerSwapPosTbl`
(walk targets). `unusedProc` is a process pointer that is deleted on close but
never set.

`duelcall_` mirrors `boardcall_` (`Start`, `Exec`, `ReturnProc`, `ObjectSetup`).

### Party board events and result overlays

Small single-process overlays share a skeleton: `<prefix>_ObjectSetup` (entry),
`<prefix>_MainProc` (the scripted sequence, sets `omSysExitReq`),
`<prefix>_ExitCheckObjMain` / `<prefix>_ExitObjMain` (wait for the request, then
the wipe), `<prefix>_SysInit`/`SysClose` (board model/motion libraries),
`<prefix>_BackInit`/`BackClose` (background) or `<prefix>_CameraInit`/`CameraClose`
(camera process), as in the board intros. A per-object state machine stored in a
function pointer uses `<Thing>Idle` for its empty state and `<Thing>Destroy`
for the process destructor (`chancetime_HostIdle`, `chancetime_HostDestroy`).

- `koopa_` (Bowser event): `Roulette` is the five-window event slot
  (`koopa_RouletteCreate`/`ObjMain`/`Kill`, `koopa_rouletteEventTbl` holds the
  event per window, `koopa_eventFuncTbl` the handlers). Handlers follow MP4's
  `ExecBowser*`: `CoinTakeExec`, `CoinTakeAllExec`, `SuitGiveExec`,
  `PhoneGiveExec`, `RevSetExec`/`RevResetExec` (Reverse Mushroom effect on all
  players), `ShuffleExec` (space swap), `RevoExec` (Bowser Revolution, coins
  averaged), `LeaveExec`. `SpellEffExec` is the growing spinning model shown when
  Bowser casts one.
- `last5_`: `KoopaExec` (Bowser takes 10 coins from a player chosen by rank) and
  `StarExec` (Millennium Star gives 10 coins); `rankPlayerTbl` maps rank to player.
- `majinlamp_` (Lucky Lamp ride): `Lamp` (the lamp model the player rides),
  `Tunnel` (scrolling `bg_in`/`bg_out` tunnel model), `PosMove`/`ArcMove`/`RotMove`
  object movers tracked in `majinlamp_moveObjTbl`.
- `chancetime_`: `Block` / `Reel` (the three spinning blocks; `reelTbl`, left and
  right reels pick players, the centre one the action), `Panel` (the drawn frame
  that drops in, `PanelDraw` hook), `Host` (the two Toads; `HostL`/`HostR` their
  jump-in objects), `Dancer` (the five intro Toads), `Transfer` (coins/stars
  flying between the two chosen players), `action` (centre reel result,
  `chancetime_actionAmountTbl`), `Event` (the window/message controller process).
- `boardresult_` / `duelresult_` (end-of-game bonus stars and winner) share base
  names: `IntroExec`, `ResultExec`, `BonusStarExec`, `Host` (announcer model with
  `hostAnimTbl`), `starMdl` (Millennium Star), `Platform` (cloud seat each player
  stands on), `Cloud` (scrolling and passing cloud layers, `CloudPassProc`),
  `CoinNum`/`StarNum` (rank-number sprites over players), `Firework`
  (`FireworkCreate` + setters; bursts into the winner's face sprite,
  `FireworkShapeSet`), `Spiral` (unused spiral particle effect). The `staff`
  overlay contains copies of the Firework code.
- `boardresult2_` / `duelresult2_` (records screen) share base names: `Rank*`
  (first page, final ranking rows), `Stat*` (second page, scrollable stat table;
  `statScroll` first column, `statCursor` selected column, `StatTopMaskGet` mask
  of players holding the best value), `hostGuide` (talking Toad guide).
- `ModelAnimCreate`/`ModelAnimSet`/`AnimDataRead` are the shared hmf texture
  animation helpers (`opboardtutorial_` names).

### Story mode overlays (mstoryN)

Story-mode chapter cutscenes. Each overlay picks a scene from
`GwPlayer[0].coin` (chapter) via `<prefix>_sceneCreateTbl` and marks it seen
in `<prefix>_sceneFlagTbl` (a seen scene can be skipped with START,
`<prefix>_skipOnF`). mstory1 holds the Star Stamp award scenes for chapters
1-3 (flags 52/54/56); mstory2 holds the chapter intros (scenes 1-4, flags
51/53/55/57: the Millennium Star shows the chapter's Star Stamp, the chapter
rival appears from the animated background model and both are sent off to the board) plus
scene 0 (no flag; Tumble and the Star ask whether to begin, "yes" leaves via
`MgStoryStageGoto`, `mstory2_SceneStageGoto`/`stageGotoF`); mstory3-5 hold
two scenes each (see below). Every mstoryN has
its own copy of the shared helpers (there is no shared library), so reuse
these base names with the overlay's prefix:

| Role | Name |
|---|---|
| Entry setup / scene state machine (wipe, START skip, exit) / `omSysExitReq` handler / camera | `ObjectSetup`, `SceneObjMain` (`sceneState`), `ExitObjMain` (`exitF`), `CameraObjMain` (`cameraPos`/`cameraTarget`/`cameraUp`) |
| Request the end of the scene (state 3) | `SceneEnd` |
| Background sprite + model | `BackCreate`, `BackDispOn`/`BackDispOff`, `backSpr`, `backMdl` |
| Star Stamp card (7 stamps; new one fades in with sparkles) | `StampCardStart(stampNo)`, `StampCardProc`, `StampCardDoneCheck`, `stampCardSprTbl`, `stampSparkSprTbl`, `stampFadeSpr`, `stampPosTbl`, `stampSprFileTbl` |
| Message window (`HuWinExCreateStyled`) | `WinCreate`, `WinOpen`, `WinClose`, `WinMesExec` (set + wait), `WinMesSet`, `WinMesWait`, `winId`; `padNo` = the human pad that may advance it |
| `-(chr == GwStory.unk1)` | `PlayerChrCheck` |
| Actor movers (chancetime names) | `ObjPosMove[V]`, `ObjPosMoveEx` (Vec + face-direction flag; float form `ObjPosMoveExXYZ`), `ObjRotMove[V]`, `ObjLinkPosMove*` (linked model follows full y), `ObjForwardMove`, `MotionEndWait`/`MotionEndCheck`, `HmfAnimSet` |

mstory2 additions: `SceneInit` (body of `ObjectSetup`), `sceneNo` (clamped
`GwPlayer[0].coin`), `ExitWipeObjMain`/`ExitWaitObjMain` (wipe out, then return
or stage goto), `WinMesChrNameExec` (message with the player's character name
inserted), `WinChoiceGet`, `BackSprDispOn`/`Off`, `BackMotionStart` (animates the
background model, SE 0x216, as the rival enters), `ObjBackwardMove`, `ObjPosMoveAccel`, `ObjTargetFace` (shared
here, per-scene in mstory1).

Each scene file `sceneN.c` uses `<prefix>_Scene<N>` / `<prefix>_scene<N>`
for everything it defines, even helpers duplicated per scene
(`mstory1_Scene0PathCreate`/`PathPosGet`/`PathKill` = `opboard_Path*`). Actors
live in `scene<N>WorkTbl` (`StoryObjWork[8]`, a per-slot obj + state func as
in chancetime; `unk_08` actor state/flags, `unk_0C`/`unk_10`/`unk_14` the
looping-SE on flag / SE number / playing SE id used by `ObjSeLoop*`; mstory2
uses the 0x14-byte variant `Mstory2ObjWork` without the SE id) and are named by role: `Player`, `Tumble` (host, model
0xA0075, with face anims `TumbleFaceAnimTbl`/`TumbleFaceSlot`), `Rival` (story
rival, swapped when the player is that character), `Koopa` (Bowser), `KoopaJrA`/`KoopaJrB`
(Baby Bowsers), `Star` (Millennium Star), `Stamp` (the flying Star Stamp
model), `Event` (actor-less slot running the scene's main script:
`Scene<N>EventProc`/`EventExec`, `EventIntroExec`; scene-0 choice branches
`EventStartExec`/`EventCancelExec`). mstory2 adds the per-actor states
`PlayerCardShow`/`CardHide` (holds up item model 0x1D000A, probably the stamp card, on `item_hook`,
`scene<N>ItemHookName`), `<Actor>Step`, `<Actor>KnockBack`, `<Actor>Exit` (runs
off to the board), `<Actor><Target>Face` (per-frame `ObjTargetFace` state),
`TumbleLand`, `RivalPose`/`RivalLuigiPose`, data `scene<N>FrontRot` (zero
rotation shared by several actors), `scene<N><Actor>AnimNameTbl` (per-character
face-anim joint names), `scene<N><Actor>FaceSlot`, `scene<N>PlayerChr`/`RivalChr`,
`scene<N>StarFloatStopF`, `scene<N>Bss` (the misaligned per-scene s16 group).

mstory3 (overlay 0x6D) has two scenes picked by `GwPlayer[0].coin` (clamped to 1):
scene 1 (flag 59, story scene 10 = after stage 8, the chapter-5 board) is a
copy of the mstory2 chapter-intro template (`mstory2_Scene4*` names with
`Scene1`; rival Mario, or Luigi when the player is Mario; work struct
`Mstory3ObjWork`, the 0x14-byte variant). Scene 0 (flag 61, story scene 12 =
after stage 10) is unique: the player receives the sixth Star Stamp
(`Scene0PlayerStampExec`, `Stamp` = the stamp model flying into the card), then
`Daisy` runs off, `Waluigi` appears from the animated background and a second
stamp model (`StampB`, spinning over model 0x1D0013) flies to him; `Koopa`
arrives, the `Cloud` (fight-cloud model 0x1D0030 with random sparkle models,
`CloudStarUpdate`) covers Koopa and Waluigi, and `KoopaJrA`/`KoopaJrB` carry
Koopa off. Its main script is split into `Scene0EventIntroExec`, `EventExec`,
`EventEndExec`. Extra per-actor states: `<Actor>Turn<k>` (rotation only),
`<Actor><Target>Face` per-frame face states (`PlayerWaluigiFace`),
`<Actor>ReactTurn` / `<Actor>LookAround` (multi-step turns driven by
`unk_08`), `<Actor>Dash`, `<Actor>StepBack`, `<Actor>Shake` (rot.y wobble),
`<Actor>Enter`; data `scene0EventRot<k>` are mutable rotation targets in .data
used by the event script on several actors. Some states are run from another
actor's slot (`Scene0WaluigiAppear`, `Scene0TumbleWalk` and `Scene0StampBDrift`
run in Daisy's slot); they are named after what they move.
`mstory3_ObjLinkPosMoveEx` is mstory1's helper with the linked model kept 5
units lower (shadow). The misaligned BSS groups are `mstory3_scene1Bss` and
`mstory3_scene1ChrBss` (`scene1PlayerChr`/`RivalChr`; scene 0 indexes past it
for `scene0CloudStarTimeTbl`).

mstory4 (overlay 0x6E, flags 62/63) holds the last two story scenes. Scene 0
(story scene 13) follows the mstory1 Star Stamp template: `Waluigi` speaks and
runs off (`Scene0WaluigiExec`) and the player receives the seventh stamp
(`StampCardStart(6)`). Scene 1 (story scene 14) is the ending: the `Star`
vanishes (`Scene1StarVanish`), Tumble's dice opens (`TumbleSpin`, `TumbleHopTurn`)
and a second Millennium Star model on Tumble's object (`StarB`, model 0xA015F with
`c221_000-aura_N` nodes; `Scene1StarBPosMove`/`FlyUp`/`SpinPosMove`,
`StarBFloatProc`) rises into the sky (`Scene1StarFlyUpExec`, `StarSpinExec`). Then
full-screen pictures (`Pic`: `Scene1PicCreate`/`PicDispOn`/`PicTPLvlSet`/
`PicSeqKill`, `scene1PicFileTbl`), a constellation of sparkle sprites
(`Spark`, `scene1SparkGroupTbl` of `Mstory4SparkGroup`, `Scene1ConstellationExec`),
then on the duel-board background (`MBDBackCreate`, `mbdBackF` tells the exit
code to kill it) the player is shown as the Superstar (`Scene1SuperstarExec`,
character title sprites `Scene1TitleCreate`) with `Firework`s
(`Scene1FireworkCreate`/`Proc`/`Burst`/`Hook`, `Mstory4FireworkWork`).
`Vignette` = the four mirrored quarter sprites (0x1D0028) shown while the star
rises; `Scene1CameraDebugProc` is an unused pad-driven camera tuner. Scene 1
carries copies of the engine `Effect*` particle helpers (`mstory4_EffectCreate`
etc., `mstory4_effectScaleWobble`). `Scene1EventExec` is still `INCLUDE_ASM`.

mstory5 (overlay 0x6F, flags 58/60) has two more Star Stamp scenes on the mstory1
template. Scene 0 (story scene 9) awards the fourth stamp; then `Koopa` and the
`KoopaJrA`/`KoopaJrB` arrive and Koopa breathes fire (`Fire`: `Scene0FireProc`
updates 16 `Mstory5FireParticle` sprites in `scene0FireParticleTbl`,
`Scene0FireEmit` is the emit state run in `scene0FireWork`). Scene 1 (story scene
11) awards the fifth stamp; `Daisy` enters from the animated background
(`DaisyEnter`, `ObjPosMoveAccelXYZ`, footstep SE fade `DaisySeFadeIn`), the
second stamp model is shown to her (`StampBShowExec`), `Koopa` appears and is
blasted away by the Star, which swaps to alternate eye models
(`Scene1StarEyesASwap`/`EyesASet`, `EyesB*`). Scene 1 has two actor-less slots
outside the table, `scene1EventWork` (`EventProc`, `EventExec`, `EventMesExec`) and
`scene1SubEventWork` (`SubEventProc`; also runs other actors' states). Shared
states of several actors are `Scene1GroupStepBack`/`GroupTurn`; model 0x83
(shown on knock-back, `scene1ShockMdl`) is the shock effect used by
`<Actor>KnockBack`.

`storycall_ObjectSetup` maps `storySceneNo` to the cutscene overlay and scene
(0x6B-0x6F = mstory1-5, scene index in `GwPlayer[0].coin`).

`storyresult_` (story stage result / save prompt) reuses the minigame
library's `MgStoryStat*` names for its copies (`StatSprSet`, `StatResultDisp`,
`StatRankMarkDisp`, `StatPageSet`, `StatExec`, `StatCreate`/`Kill`, `RankGet`,
and the `mgStory*Tbl` data with the `storyresult_` prefix; `pageTbl` = stage
kind per story stage: 0 party board, 1 duel, 2 boss). Its own parts: the
msetup-style camera helpers (`CameraPresetSet`, `CameraUpdate`, `CameraProc`,
`CameraKeyframeExec`, `cameraFov`/`Near`/`Far`), `ModelEntryPosSet`/`ReadAll`,
`Rand*` (copies of `MgRand*`), `StageClearCheck` (entry check; a lost stage
goes back to the story start), `StageRankCalc` (`PartyRankCalc`,
`DuelRankCalc`, `BossRankCalc`), `StageResultProc` (rank message and continue /
save prompt), `FinalResultProc`/`FinalStatProc` (after the last stage, saves
the per-character record), `DebugStatProc`; save helpers `ProgressSave`/
`ProgressSaveCntGet` (suspended story progress, `GwStory.unk64..`) and
`RecordSave`/`RecordCntGet` (per-character clear record). Per actor: `Scene<N><Actor>Proc` (creates the object and runs its
state func), `...Destroy`, `...Exec` (main scripted sequence), smaller states
(`PlayerTurn1`, `TumbleHop`, `TumbleExit`, `StarTurn`, `StampFlyExec`), the
empty state `Scene<N>ObjIdle`, the scene entry `Scene<N>Create` and looping SE
helpers `Scene<N>ObjSeLoopStart`/`Stop`/`Proc`. Data: `scene<N><Actor>StartPos`
(rodata initial position), `scene<N><Actor>Pos` (bss copy),
`scene<N><Actor>DestPos<k>`/`DestRot<k>` (targets passed to the movers,
numbered in address order), `scene<N>UnusedPos<k>`/`UnusedRot<k>` for
unreferenced vectors, `scene<N>ShadowMdl`, `scene<N>PlayerMot<slot>Tbl`
(per-character motion files by motion slot).

### Frontend overlays (msetup, staff, option, filesel, opening, modesel, mchar, boot, slerror)

Frontend overlays share the storyresult skeleton: `ObjectSetup`,
`ExitCheckObjMain`/`ExitObjMain` (`exitCnt`, `exitMode`, `exitOvlNo`,
`exitEvtNo`, `wipeType`/`wipeTime`), the camera helpers (`CameraPresetSet`,
`CameraUpdate`/`CameraProc`, `CameraKeyframeExec` with `cameraKeyTbl`-style
`MsetupCameraKeyframe` lists, `cameraFov`/`Near`/`Far`/`Rot`/`Pos`/`Target`,
`cameraLookF`), `ModelEntryPosSet`/`ModelEntryReadAll`, `Rand*` (`randSeed`),
`PlayerConfigInit`/`playerConfig` (`MsetupPlayerConfig`) and `padNo` (the
controlling pad). Menu vocabulary:

| Concept | Name |
|---|---|
| Message window helpers (one window id in `winId`) | `WinProc` (creates/opens windows, driven by `winMode`), `WinMesSet`, `WinMesWait` (wait + choice), `WinInsertMesSet`, `WinHomeClear`, `WinAttrWait`/`WinAttrSet`, `WinInputGet` |
| Pad helpers | `PadBtnGet` (buttons with the stick folded into the D-pad), `PadBtnDownGet(pad, &prevBtn)` (newly pressed), `StickQuadrantGet` |
| Sprite cursor process (`MsetupCursorState`: fades on state 1/2, eases to `positions[selection]`) | `CursorProc`; 2D nearest-item search `CursorNearestGet` / `CursorPadNextGet` (`...CursorPosTbl` = `s16 [n][2]` screen positions) |
| One setting screen run from a menu state table | `<Thing>Select` (whole screen, returns to state 0), `<Thing>Choice` (one choice loop inside it, returns the selection or -1 on B) |
| Menu state dispatcher | `MenuProc` + `menuFuncTbl` (state 0 = `MenuIdle`); the setup flow calls each screen through `<Mode><Thing>Step(step)` functions in `<mode>StepTbl` that return the next step (negative = leave) |
| Left/right bouncing arrows | `ArrowObjCreate`/`ArrowObjMain`/`ArrowObjKill` (work[0]: 1 fade in, 2 fade out, 3/4 bounce left/right) |
| Flipping 3D panel (model 0x140003) | `Panel*`: `PanelCreate[Ex]`, `PanelSpinMove` (spin in/out), `PanelMove` (to `MsetupModelTarget` lists `...PanelOpenTbl`/`panelCloseTbl`) |
| Per-player character on the stage | `PlayerProc` (state machine in `playerWorkTbl`), `PlayerProcCreate[Ex]`/`Kill[Ex]` |
| Setup "summary" (chosen board/turn models shown during later screens) | `SummaryProc`/`SummaryCreate`/`SummaryStateSet`/`SummaryEntrySet` |

msetup modes (`setupMode` = `omovlevtno`, `setupProcTbl`): 0 `PartySetupProc`,
1 `DuelSetupProc`, 2/3 `StoryPartySetupProc`/`StoryDuelSetupProc`, 4
`StorySetupProc` (new story file: character, difficulty and minigame-pack menus,
`StoryMenuProc`), 5 `MgModeSetupProc`, 6 `MgMode1PSetupProc`, 7/8
`TutorialPartySetupProc`/`TutorialDuelSetupProc`. Settings: `PlayerNum`
(human count), `Chr` (character select; `ChrInfo` is the duel info card),
`ComLevel` (CPU difficulty; `comLevelEasy/Normal/Hard/VeryHardStr`), `Handicap`
(stars; duel uses `DuelHandicap`), `Board`, `Turn` (`TurnDialChoice` over the
"20turn"/"35turn"/"50turn"/"q_turn" nodes, `TurnCustomChoice`), `Bonus`
(bonus stars on/off, flag 0x1B), `MgPack` (minigame pack, flag 0x20 / story 0x29; board code calls the set state `Easy`),
`Confirm`. `MpAttrIdxGet` comes from the debug string "mSetupGetMpAttrIdx".

staff (credits): `MainProc` runs the sequence; `Back*` (starry background
layers `BackStar*` and title sprites), `Host` (the two story-mode hosts, Tumble
and the Millennium Star model 0xA0122, orbiting in), `Star` (the 0xA015F
Millennium Star model following `Path*`), `CreditRollProc` walking
`creditTbl` (`creditSec<k>Tbl`, k = order, = role message 0x6400 + k),
`TextLine*` sprite text lines in two fonts (`role` titles, `name`s), `Cast*`
(three recycled 3D models scrolling with the credits, `castMdlTbl`), `Finale*`
(characters on the duel-board background), `End*` (Tumble drops in, "END"
sprites). `Firework*`/`ParticleAdd`/`Spiral*` reuse the boardresult names.

**Shared sprite/model/window helper layer** (opening `op_*`, modesel, option,
filesel; copies of the same file). Use the opening's real names with the
overlay prefix: `AnimIdGet`/`EspIdGet`/`AnimCreate`/`AnimKill`/`EspCreate`/
`EspKill`, `Spr*` (`SprCreate`, `SprBGCreate`, `SprKill[All]`, `SprDispOn`/`Off`,
`SprBGDispOn`/`Off`, `SprPos`/`Scale`/`Alpha`/`Attr`/`Pri`/`BankSet`...),
`Model*`/`Motion*` (`MotionFlagSet`/`MotionFlagReset` = set / clear motion
attribute bits), `BGSprCreate`/`Kill`, and the window table `Win*`
(`WinMesConv` copies a string message into heap memory, `WinCreate`
dispatches to `WinType<n>Create` by style, `WinKill[All]`, `WinMesSet`,
`WinInsertMesSet`, `WinChoiceGet`, `WinMesWait`, `WinIdGet`). Init helpers:
`UtilInit` (calls `SprInit`, `ModelInit`, `WinInit`); data `sprTbl`, `animTbl`,
`modelTbl`, `winTbl`, `bgAnim`/`bgSpr`. `ObjectInit` is the shared
`omInitObjMan`/camera/light setup (as `op_ObjectInit`); the overlay entries
call it and are `<Thing>ObjectSetup`. `CameraDebugExec` is the pad-driven
camera print loop ("POS:"/"A T:"/"U P:"). `StickBtnGet` folds the stick into
latched D-pad bits; `RumbleObjMain`/`RumbleStart` pulse the rumble pak on exit.

option (overlay 0x7B): three 3D rooms. `Room` is the hub (entries 0-3,
`RoomObjectSetup`, `RoomFromL`/`FromR`/`FromRecordObjectSetup` by the door the
player came back through), `SoundRoom` (entries 4/5: stereo/mono speakers,
`SoundTestExec` with the parrot model over `soundTestTbl`, `MusicTestExec`
with the band model over `musicTestTbl`), `RecordRoom` (entry 6:
`PartyRecordExec`/`DuelRecordExec` = per-character board records,
`MgRecordExec` = minigame records, copied from mgmode). Each room has
`<Room>Create`, `<Room>Proc`, `<Room>Init`/`Close` (models and camera),
`<Room>Choice` (selection loop), `<Room>Move` (D-pad step between spots),
`<Room>Decide` (A press; -1 = stay) and `<Room>Cursor*`. The `Menu*` functions
(`MenuSprPosSet`, `MenuMdlIdGet`, `MenuMotSet`, `MenuWinCreate`,
`MenuWinChoiceGet`...) are the thin wrappers over the helper layer that the
room code calls. Camera: `cameraWork` with `CameraMove` (linear),
`CameraEaseMove`, `CameraTurnMove[Rev]` (turns the view direction one way or
the other, `cameraTurnDir`), `CameraMotionStart` (camera from a model motion),
`CameraManualStart`; `ScreenPosGet[Ex]` projects a 3D point. `LookAt*` are
objects that keep a model facing the camera; `SeObj*` stops the parrot
animation when its sound ends.

filesel (overlay 0x7A): `fileWork` holds the three file boxes (models 0-2,
number labels 3-5, `FileMdlCreate`). `FileMenuExec`/`FileMenuChoice` drive the
top menu (files, Copy/Erase buttons `CopyEraseBtn*`, file names), `FileDecide`
handles the chosen file (new file -> `NewNameEntryExec`), `ModeChoice` picks
story vs. other modes, `CopySelect`/`EraseSelect` with `FileTargetChoice`.
Name entry: `NameEntryExec`, `NameInputExec` (`nameInput`), keyboards
`Hiragana`/`Katakana`/`Alpha` (`...Input`, `...CharGet`, `...Tbl`),
`NameOption*` (option row), `KeyCursor*`. File-box motion objects:
`FileIn`/`FileOut` (fly in/out), `FileRaise`/`FileLower` (to the corner and
back), `FileJump`, `FileBreath`/`FileWobble`/`FileCopy` (in `fileAnimTbl`).
Info panels: `StoryStat*` (left, story progress) and `BoardStat*` (right,
suspended party/story boards).

Helper-layer additions: `SprPriSet`/`SprBankSet`, `WinScaleSet`/`WinPosSet`/
`WinDispOn`/`Off`/`WinPriSet`, `PadBtnWait` (sleep until a button), data
`winMesTbl`/`winTypeTbl` (field views of `winTbl`) and `modelScaleTbl`.
Camera helpers shared with option: `CameraAngleCalc`, `CameraDirLerp`,
`CameraPosGet`/`PosSet` (copy the `cameraWork` pos/at/up),
`CameraEaseMove`/`CameraTurnEaseMove` (+ `...ObjMain`, `CameraMoveKill`),
`CameraShakeCreate`/`ObjMain`/`Kill` (`cameraShake`), `CameraMotionStart`/
`CameraMotionProc` (camera driven by a model motion), `CameraManualStart`/
`CameraProc` (camera from `cameraWork`). `LookAtAngleCalc` is the yaw that
faces the camera. Field-view aliases of a word use the `Half` suffix
(`modesel_winPosYHalf` = low s16 of `modesel_winPosY`).

opening (`op_`; entries `TitleObjectSetup`, `DemoReturnObjectSetup`,
`DemoObjectSetup`): `Title*` is the title screen, `Demo*` the attract-mode
demo event (`DemoEvent`). Demo objects live in `demoObjTbl` (16 slots, field
views `demoObjTime`/`MaxTime`/`Work`/`ParamA`/`ParamB`/`EndX`/`EndY`/
`AngleX/Y/Z`/`BodyNode`/`ShadowNode`): `DemoMotInterval*` (plays a one-shot
motion every N frames), `DemoMotRestart*` (restarts a motion), `DemoJump*`
then `DemoFloatMain` (model with a body and shadow node), `DemoFly*`/
`DemoFlyAway*` (wandering flight then exit). `SpiralEff*`/`SparkEff*` are
particle models (msetup's `SpiralEff*`), `SparkTrailExec` runs two spark trails;
`AngleStep` (step an angle toward a target), `AngleLerp`, `DirLerp` (returns
the angle form of `CameraDirLerp`). `ContError*` is the controller-error sprite.

modesel (overlay 0x77): `MainProc` runs `MenuExec` (selection loop over menu
spots: `MenuMove` on the D-pad, `MenuDecide` on A, `MenuMesSet` sets the host's
message, `SpotFocus` moves camera and cursor). `Spot` = selectable spot in the
room (`spotPosTbl`, `SpotPosGet`, `SpotEff*` pulse effect), `Cursor*` = the 2D
pointer sprite. `Host` is model 10 (`HostEnter`/`Float`/`Exit`/`Jump`/`Fall`),
`Star*` the three star models 7-9 (`StarNode*` positions the star and shadow
nodes, `StarBob`/`Land`/`Blink`/`Jump`/`Spin`/`Hold`/`Fall`). `BoardStat*`
shows the suspended party and story boards (as in filesel), `FileInfo*` the
file/chapter sprites at the top left, `HelpExec` the paged help window,
`Stage*` creates/kills all room models, `BoardNoGet`/`BoardIdxGet`/
`BoardTypeGet` decode `boardNoTbl` (record index -> board).

mchar/mchar2 are debug character motion viewers ("MOTIONNO.", "M_TIME:"):
`ViewerObjInit`/`ViewerObjMain`, `ChrModelRead`, `ChrMotionChange`,
`CameraObjMain`/`CameraReset`, data `chrNo`/`motNo`/`mdlNo`, `chrMdlTbl`/
`chrMotTbl`, `motNameTbl`. boot (`boot_`): `LogoProc` shows the three boot
logos, `SkipObjectSetup`/`SkipCheckObjMain` (START skips, `skipF`). slerror:
`MainProc` shows the save-error sprites selected by `SLFormatFlags`.

### Mini-Game mode overlays (mgmode, mgenter)

mgmode (overlay 0x69) is the Mini-Game House: three 3D rooms picked by
`omovlevtno` in `mgmode_ObjectSetup`. `Room` is the hub (`RoomProc`, entries
0/1/6/7: fresh, back from a minigame, back through the battle / Game Guy door),
`Battle` the battle room (`BattleRoomProc`, entries 2/4) and `Gamble` the Game
Guy room (`GambleRoomProc`, entries 3/5). Each room has `<room>CameraPresetTbl`
(`ModeCameraPreset`, set with `CameraPresetSet`/`CameraPresetMove`; the room's
state machine switches on `cameraPresetNo`), `<room>MdlDefTbl` (model list for
`MdlListCreate`, results in `mdlTbl`/`motTbl`) and `<room>CursorPosTbl`.
Field-view aliases into those arrays are named by element index (`mdlTbl7` =
`&mdlTbl[7]`, `motTbl16`), since their meaning changes per room.

| Concept | Name |
|---|---|
| Model / sprite lists from a `-1`-terminated def table (datalist.c) | `MdlList*`, `SprList*` (`SprListCreate`, `SprListPosSet`, `SprListNumSet` = digit sprites); def tables `...SprDefTbl` / `...MdlDefTbl`, created lists `...SprTbl` |
| 2D cursor sprite gliding between `cursorPosTbl` spots | `CursorProc`, `CursorSelSet` (jump), `CursorSelMove` (glide), `CursorDispSet`, `CursorDisableSet`, `CursorPadNextGet` (msetup name) |
| Minigame screenshot (HVQ image 0x17xxxx into one sprite, triple-buffered) | `MgPicCreate`/`MgPicLoad`/`MgPicKill`, `mgPicSpr`, `mgPicBufTbl` (also in mgenter) |
| D-pad folded into the stick values | `DpadStickSet` (also in mgenter) |
| Falling confetti particles over players who scored | `Confetti*` (`ConfettiCreate` returns a slot, `ConfettiOn`/`Off`) |
| Hub minigame list | `Shelf` = one minigame type (`book_N` nodes, `ShelfSelect`), `Book` = one minigame on it (`BookSelect`, `bookPosTbl`); per-type lists `typeMgTbl`, `typeMgNumTbl`, `typeUnlockNumTbl` (`MgListBuild`); `mark` = `mgDataTbl` flag bit 15 (badge sprite) |
| Battle setup | `Goal` = stars to win (3/5/7, `mgModeSelNo`), `Type` = minigame type (`mgModeType`), `Team*` = team arrangement choice for 2-vs-2 / 1-vs-3, `Board` = star tally sprites, `StarPlayer*` = players who won a star this round |
| Game Guy room | `Bet` (coins wagered, `BetChoice`), `Payout`, `Board` (calculation sprites), `Coin` (coin counter sprites), `Title` (minigame name as `GAMEMES`), `Spot` (software-drawn spotlight sprite, `SpotUpdate`), `Reward` (1000-coin reward drop) |

`ZClearHook`/`zClearF` clear the depth buffer while a room is entered from a
minigame. `RecordSave` writes the common save (mirrors `storyresult_RecordSave`).

mgenter (overlay 0x68) is the screen shown before a minigame in Mini-Game mode:
`MainProc` (screenshot + title, A to start), `StageMainProc` (minigames with
several stages: stage pictures from `MgPicProc`/`StageNameProc` plus a 3-model
`OptionProc` carousel, used by `mgDataTbl[70]`), `NumMainProc` (pick a value
100-1000, `mgDataTbl[30]`), `ArrowProc`/`ArrowPosSet` (left/right arrows);
`SkipObjectSetup` jumps straight to the minigame.

### Minigame instructions (inst)

`inst_` (minigame instruction screen) uses MP4's `instDll` names where the code
matches, without repeating `Inst` after the prefix: `inst_PlayerMain`
(`InstPlayerMain`), `inst_HostMain` (`InstHostMain`), `inst_WinMain`
(`InstWinMain`), data `inst_mgNo`, `inst_hostNo`, `inst_winPage` (`instPage`),
`inst_backFileTbl` (`instBackFile`), `inst_boxFileTbl` (`instBoxFile`). The
sequence object itself is `inst_MainObjMain` (`InstMain` in MP4 is a process;
here it is an `omAddObj` function). Every actor keeps its state function in an
`InstObjectState` (`inst_<thing>Work` / `inst_<thing>Func`) with states named
`<Thing>Wait`, `<Thing>Open`, `<Thing>Close`, `<Thing>Idle`; `...Now` variants
jump straight to the end state when the intro is skipped (`inst_introSkipF`,
minigame already unlocked).

| Term | Meaning |
|---|---|
| `Box` | the instruction board model (`inst_BoxMain`); `Pic` is the HVQ screenshot on its `gamen` node (`inst_PicLoad`, `inst_picNo`), `frame` its frame |
| `Plate` | per-player character plates hooked onto the board (`hook_ao`/`aka`/`midori`/`last` = team colour, `inst_plateColorTbl`) |
| `Hook` | node-name lists per minigame type (`inst_hookTbl[type][0]` players, `[1]` item prizes; `inst_mg4PPlayerHooks`, `inst_itemItemHooks`) |
| `Host` / `ItemHost` / `BattleHost` | Tumble (default), model 0xA0000 (item minigames), model 0xA00A5 (battle/duel; holds the coin pot); `inst_hostNo` 0/1/2 |
| `Practice` | R-button practice mode (`inst_PracticeOn`/`Off`, `inst_practiceF`, the "PRACTICE" label `inst_practiceMes`); `inst_practiceRetF` = returning from a practice run |
| `ItemPrize` | the five prizes drawn for an item minigame (`inst_ItemPrizeInit`, weight tables `inst_itemPrizeA/BWeightTbl`) |
| `Title` | minigame name (`GAMEMES` `inst_titleMes`) on the title sprite that slides in (`inst_WinTitleIn`) |
| `CoinPot` | battle minigame coin pot digits under the title |

### Minigame result overlays (mgresultboard, mgresultbattle, mgresultduel, mgresultdealer)

Shared skeleton (all four): `ObjectSetup`, `MainObjMain` (`mainState`,
`mainTimer`), `ExitObjMain` (`exitWipeF`), `CameraInit`, `BackInit` +
`BackDimCreate`/`BackDimDraw` (board background with a translucent black
overlay, `boardBackTbl` = background per board), `playerOrderTbl` (players
sorted by `group`), `HmfAnimSet` (same helper as mstoryN). Process-backed
actors use `<Thing>Proc`, `<thing>Obj`/`<thing>Func` or `<thing>Work`, and
states `<Thing>Idle`/`<Thing>Destroy`. Falling coin effects use the same names
in battle, duel and dealer: `CoinProc`, `coinTbl` (coin sprite models),
`coinEffTbl` (landing sparkle), `coinSprMdl`/`coinEffSprMdl`, counters
`coinNum`, `coinMax`, `coinOutCnt`, `coinInterval`, `coinTimer`, `coinVibF`.
`PlayerReactStart`/`PlayerReactWait` play the win/lose motions and wait.

- `mgresultboard_` (party board scoreboard): a split-flap board. `Flap` = one
  flipping panel (`UnkTemp`: state, current/next bank, current/next model);
  rows per player made of `Rank`, `Face` (character face, `faceBankTbl`
  [chr][face]), `CoinIcon`, `StarIcon` and `Score` digits (`StarFlip`,
  `CoinFlip`, `...PlusFlip` = gained-coin variant with a `+` glyph, `...Set`
  = immediate). `RowShuffle` spins a row to random values, `RowSet` shows the
  real values, `RowDimOn`/`Off` move a row behind / in front of the dim overlay
  (camera 0/1). `speed` is 4 while A is held.
- `mgresultbattle_`: `CoinCalc` splits `mgBattleCoinPot` by rank
  (`coinShareTbl`, `coinRest` = leftover given to a weighted random player);
  `Host` is model 0xA00A5 flying over the players dropping coins
  (`HostFly`, `CoinDrop`); `Podium` (rank podium models, `PodiumUpdate` keeps
  players on the `chara` node); `CoinNum` (coin count sprites over players).
- `mgresultduel_`: `GateGuy` (as on the duel boards; `GateGuyBell*` turns the
  bell counter in `GwSystem.bank_coins`), `Player1P`/`Player2P` (`Enter`,
  `CoinWatch`, `Win`, `Lose`), `Host` = Tumble flying on a spline
  (`hostPathTbl`) and stomping the Gate Guy, which spouts coins to the winner
  (`CoinSpout`, `winSide` -1/1/2 = 1P/2P/draw, `prizeCoin`).
- `mgresultdealer_` (Game Guy result): `bet` x `payoutRate` shown by the
  `Calc` sprites (`CalcOpen`, `CalcCount`, `CalcClose`); win = `CoinRain` and
  `Confetti` particles, lose = `Fade` (dark screen overlay) and `Drop` (an
  object falling on the player's head, model 0x83 shock effect).
- The `...MainBss` structs are the misaligned bss groups (`mainCnt` +
  `seIdTbl` in mgresultboard, `bet` + `playerOrderTbl` in mgresultdealer).

### Debug overlays (selmenu, selmenu2, sldebug, storydebug, meschk)

selmenu/selmenu2 are the debug minigame select menus (selmenu2 is an older copy
with a different list; both share base names). Names follow MP4's `selmenuDll`
(`SMInit` -> `MenuObjInit`, `SMUpdate` -> `MenuObjMain`, `SMCharUpdate` ->
`ChrSelObjMain`, `SMPlayerCfgUpdate` -> `PlayerCfgObjMain`, `CalcBtns` ->
`BtnCalcObjMain`, `MoveSMPage`/`MoveSMCursor` -> `PageMove`/`CursorMove`,
`CopyPlayerCfg` -> `PlayerCfgCopy`) with the grammar fixed. Data: `menuTbl`
(`smMenuTbl`, `SelMenuConfig` entries, 10 per `page`), `selectPos`,
`selectPosBackupTbl`, `playerCfg` (edited `GW_PLAYER` copies),
`playerCfgOptionPos`/`PlayerPos`/`SelF`, `playerDoneF`, `chrUsedF`,
`btnDownTbl` (per-pad bits: 1/2/4/8 up/down/left/right, 0x10 A, 0x20 B, 0x40 Z,
0x80 START) with key repeat `btnHold*`/`btnRepeatTimerTbl`.
`MgNameRiseObjMain` floats the chosen name up with spark sprites
(`spark*`). Strings are named after their text (`mgName201Str`, `pageFmtStr`,
`comLevelFmtStr`). `ShadowTextPrint` = `print8` with a drop shadow.

sldebug is the story save debug menu ("ALL MINIGAME ENABLE", "STORY NO.xx";
`MenuObjMain`/`MenuDecide`, `storyNo`/`storyChrNo`/`storyComLevel`), with a
pad-driven `CameraDebugObjMain` ("CROT"/"INT"/"CZOOM", `infoDispF`).
storydebug shows story and player save fields (`StoryInfoDraw`,
`PlayerInfoDraw`). meschk steps through every message file (`mesFileTbl`
= name, first/last message id) in `MesCheckExec`. Overlays that leave via a
wipe use `ExitCheckObjMain`/`ExitObjMain` with `exitF` (mchar names).
