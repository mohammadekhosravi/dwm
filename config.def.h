/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps[]    = { 0 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 4 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_border[]        = "#dc2626";
static const unsigned int baralpha = 0xdf;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
	"picom", "--experimental-backend", NULL,
	"nitrogen", "--restore", NULL,
	"xsetroot", "-name", " DWM ",
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor    float x,y,w,h         floatborderpx*/
	{ "Gimp",     NULL,       NULL,       0,            1,           -1,        50,50,500,500,        5 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1
#include "nrowgrid.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "###",      nrowgrid },
	{ "|M|",      centeredmaster },
	/* { ">M>",      centeredfloatingmaster }, */
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	/* This NULL NULL should always be the last one*/
	{ NULL,       NULL },
};

/* key definitions */
// Mod4Mask = Super key / Mod1Mask = Alt key
#define MODKEY Mod4Mask

/* 
 Go to nth tag
 { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, 

 Move a window to nth tag
 { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },

 See windows of selected tags all in once
 { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} },

 Copy or Uncopy window form nth ta
 { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} 
*/

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "konsole", NULL };
static const char *webcmd[]  = { "google-chrome-stable", NULL };
static const char *firefox[] = {"firefox", NULL};
#include "shift-tools.c"

static Key keys[] = {
	/* modifier                     key        function        argument */

	/* ****************************************************************************/
														/* Default Functionality */
	/* ****************************************************************************/

	{ MODKEY,		 			              XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = webcmd } },
	{ MODKEY,                       XK_z,      spawn,          {.v = firefox } },
	/* Make it Master window */
	{ MODKEY|ShiftMask,             XK_Return,  zoom,           {0} },
	{ MODKEY,                       XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	/* This is like switching between the two most recent tags. */
	{ MODKEY|ShiftMask,             XK_l,    view,           {0} },
	/* View all windows - regardless of tag */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },

	 /*Copy a window to all tags. */
	 /* WE HAVE MODKEY + s for this with toggling ability BUT 
		 IT DOESN'T WORK WITH DEFAULT TAG MANAGEMENT STUFF */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	/* Toggle layouts - this toggles between the most current two layouts. */
	/* { MODKEY,                       XK_space,  setlayout,      {0} }, */

	/* toggle window layout - for the focused window, this toggles between tiled and floating states. */
	/* { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} }, */

	/* ****************************************************************************/
														/* Default and Patches Layouts */
	/* ****************************************************************************/

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[2]} },
	/* For centeredmaster use 'd' as in center of centeredmaster word :)) */
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_s,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[6]} },

	/* ****************************************************************************/
														/* Patches Functionality */
	/* ****************************************************************************/

	/* Make a window visible on all tags and undo it with the same binding */
	{ MODKEY,                       XK_a,      togglesticky,   {0} },

	/* Cycle through all layouts */
	{ MODKEY,						            XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY,                       XK_period, cyclelayout,    {.i = +0 } },

	/* View the closes tag that has a client. If none acts as shiftview(Which means
		 view the adjacent tag, It basically make shiftview obsolete */
	{ MODKEY,                       XK_n, 		 shiftviewclients,   { .i = +1 } },
	{ MODKEY,	                			XK_p,			 shiftviewclients,   { .i = -1 } },
	/* { MODKEY|ShiftMask,             XK_o,			 shiftview,          { .i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_i,			 shiftview,          { .i = -1 } }, */

	/* Basically moves the window to the next/prev tag and follows it. */
	{ MODKEY|ShiftMask,             XK_n,      shiftboth,      { .i = +1 }	},
	{ MODKEY|ShiftMask,							XK_p,      shiftboth,      { .i = -1 }	},

	/* I don't find this usefull. View shift-tools for more info. */
	/* { MODKEY|ControlMask,						XK_h,      shiftswaptags,  { .i = -1 }	}, */
	/* { MODKEY|ControlMask,						XK_l,      shiftswaptags,  { .i = +1 }	}, */

	/* There are for multi montior people I guess */
	/* { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */

	/* Gaps */
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	/* This is essentially logout */
	{ MODKEY,                       XK_Escape, quit,           {0} },
	/* This is essentially restarting dwm inplace */
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

