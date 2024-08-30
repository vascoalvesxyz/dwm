/* See LICENSE file for copyright and license details. */

#define TERMINAL "st"
#define TERMCLASS "st-256color"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps	     = 1;	 /* 1 means gaps are used by default */
static const unsigned int gappx     = 15+(6*2);       /* default gap between windows in pixels */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 0;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *altbarcmd        = "$HOME/.config/polybar/bar.sh"; /* Alternate bar launch command */

static const char *fonts[]          = { "Mononoki Nerd Font Mono:size=10",
                                            "Noto Color Emoji:pixelsize=9"
};
static const char dmenufont[]       = "monospace:size=10";
static const char norm_bg[]         = "#1d2021";
static const char norm_border[]     = "#303030";
static const char col_font[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_focus[]       = "#880000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_font, norm_bg,    norm_border},
	[SchemeSel]  = { col_gray4, col_focus,  col_focus  },
};

static const char *tagsel[][2] = {
   /*   fg         bg    */
  { col_font, norm_bg}, /* norm */
  { col_gray4, col_focus}, /* sel */
  { col_font, norm_border}, /* occ but not sel */
  { col_focus,  norm_bg}, /* has pinned tag */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     	  instance     title        tags->mask   isfloating   isterminal  noswallow  	monitor */
	{ "Gimp",         NULL,        NULL,                0,            1,           0,         1,        -1 },
	{ "Steam",         NULL,        NULL,                0,            1,           0,         1,        -1 },
	{ "steam",         NULL,        NULL,                0,            1,           0,         1,        -1 },
	{ TERMCLASS,      TERMCLASS,   TERMINAL,       	    0,            0,           1,         0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile }, /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* key definitions */
#define ALTKEY Mod1Mask
#define SUPER  Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ ALTKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALTKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ALTKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *crtcmd[]  = { "cool-retro-term", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ ALTKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ ALTKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ ALTKEY|ControlMask,           XK_Return, spawn,          {.v = crtcmd} },
	{ ALTKEY,                       XK_b,      togglebar,      {0} },
	{ ALTKEY|ShiftMask,             XK_b,      toggleborder,   {0} },
	{ ALTKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ ALTKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ ALTKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ ALTKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ ALTKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ ALTKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ ALTKEY,                       XK_Return, zoom,           {0} },
	{ ALTKEY,                       XK_Tab,    view,           {0} },
	{ ALTKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ ALTKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ ALTKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ ALTKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ ALTKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ ALTKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ ALTKEY,                       XK_space,  setlayout,      {0} },
	{ ALTKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ ALTKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ ALTKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	/*{ ALTKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/*{ ALTKEY,                       XK_period, focusmon,       {.i = +1 } }, */
	{ ALTKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ ALTKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ SUPER,                        XK_comma,  setgaps,        {.i = -5 } },
    { SUPER,                        XK_period, setgaps,        {.i = +5 } },
    { SUPER,                        XK_a,      setgaps,        {.i = GAP_TOGGLE} },
	{ SUPER|ShiftMask,              XK_a,      setgaps,        {.i = GAP_RESET } },
    TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ ALTKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         ALTKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         ALTKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         ALTKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            ALTKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            ALTKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

