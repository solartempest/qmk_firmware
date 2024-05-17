<<<<<<< HEAD:keyboards/aidansmithdotdev/sango/config.h
/* Copyright 2024 Aidan Smith <aidan@aidansmith.dev>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

=======
>>>>>>> zodiarkpi:keyboards/sofle/keymaps/foureight84/config.h
#pragma once

/* The way how "handedness" is decided (which half is which),
see https://docs.qmk.fm/#/feature_split_keyboard?id=setting-handedness
for more options.
*/

#define EE_HANDS
<<<<<<< HEAD:keyboards/aidansmithdotdev/sango/config.h
=======

/* clear default encoder def */
#undef TAP_CODE_DELAY

/* encoder support */
#define TAP_CODE_DELAY 100

#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
>>>>>>> zodiarkpi:keyboards/sofle/keymaps/foureight84/config.h
