/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static unsigned int gappih    = 0;       /* horiz inner gap between windows */
static unsigned int gappiv    = 0;       /* vert inner gap between windows */
static unsigned int gappoh    = 0;       /* horiz outer gap between windows and screen edge */
static unsigned int gappov    = 0;       /* vert outer gap between windows and screen edge */
static int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static char *fonts[]          = { "JetBrainsMono Nerd Font:size=10", "JoyPixels:pixelsize=10:antialias=true:autohint=true" };
static const char col_gray1[]       = "#222";
static const char col_gray2[]       = "#444";
static const char col_gray3[]       = "#bbb";
static const char col_gray4[]       = "#eee";
static const char col_cyan[]        = "#000";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {TERMINAL, "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {TERMINAL, "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };

static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
};

/* tagging */
static const char *tags[] = { "", "", "", "",""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	*/
	/* class         instance      title       	 tags mask      switchtotag    isfloating   isterminal  noswallow  monitor */
	{ TERMCLASS,      NULL,       NULL,       	    0,              0,             0,           1,         0,        -1 },
	{ TERMCLASS,      "st",     "cmus",       	    1 << 4,         1 << 4,        0,           1,         0,        -1 },
	{ "org-jdownloader-update-launcher-JDLauncher","org-jdownloader-update-launcher-JDLauncher",NULL,1 << 4,1 << 4,0,0,0,-1 },
	{ NULL,           NULL,   "JDownloader 2",      1 << 4,         1 << 4,        0,           0,         0,        -1 },
	{ "transmission", NULL,        NULL,            1 << 4,         1 << 4,        0,           0,         0,        -1 },
	{ "wps",         "wps",        NULL,       	    1 << 3,         1 << 3,        0,           0,         0,        -1 },
	{ "wpp",         "wpp",        NULL,       	    1 << 3,         1 << 3,        0,           0,         0,        -1 },
	{ "et",           "et",        NULL,       	    1 << 3,         1 << 3,        0,           0,         0,        -1 },
	{ "pdf",      "wpspdf",        NULL,       	    1 << 3,         1 << 3,        0,           0,         0,        -1 },
	{ "zoom",       "zoom",        NULL,       	    1 << 3,         1 << 3,        0,           0,         0,        -1 },
	{ "Zathura","org.pwmt.zathura",NULL,        	  1 << 3,         1 << 3,        0,           0,         0,        -1 },
	{ "Code",       "code",        NULL,       	    1 << 2,         1 << 2,        0,           0,         0,        -1 },
	{ "QtCreator","qtcreator",     NULL,       	    1 << 2,         1 << 2,        0,           0,         0,        -1 },
	/* { "",     "",       NULL,       	    1 << 3,       0,                          0,         0,        -1 }, */
	/* { "",     "",       NULL,       	    1 << 3,       0,                          0,         0,        -1 }, */
	{ "Brave-browser","brave-browser",NULL,         1 << 1,         1 << 1,        0,           0,         0,        -1 },
	{ NULL,          "spterm",   NULL,       	    SPTAG(0),           0,           1,           1,         0,        -1 },
	{ NULL,          "spcalc",   NULL,       	    SPTAG(1),           0,           1,           1,         0,        -1 },
};
/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",	monocle },		/* All windows on top of eachother */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */
	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */
	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
	{ "[]=",	tile },			/* Default: Master on left, slaves on right */
	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */
	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
};
/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,         	  KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD,	XK_j,	ACTION##stack,	{.i = INC(+1) } }, \
	{ MOD,	XK_k,	ACTION##stack,	{.i = INC(-1) } }, \
	{ MOD,  XK_v,   ACTION##stack,  {.i = 0 } }, \
	/* { MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *termcmd[]  = { TERMINAL, NULL };

#include <X11/XF86keysym.h>
#include "shiftview.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                 push)
	/* { MODKEY|ShiftMask,		XK_Escape,	spawn,	SHCMD(TERMINAL " -e newsboat; pkill -RTMIN+6 dwmblocks") }, */
	{ MODKEY,	           	XK_grave,   	togglescratch,	{.ui = 0} },
	/* { MODKEY|ShiftMask,		XK_grave,	togglescratch,	SHCMD("") }, */
	TAGKEYS(	        	XK_1,	    	0)
	TAGKEYS(	        	XK_2,	    	1)
	TAGKEYS(	        	XK_3,	    	2)
	TAGKEYS(	        	XK_4,	    	3)
	{ MODKEY,	        	XK_5,	    	spawn,		SHCMD("wps") },
	{ MODKEY,	        	XK_6,		    spawn,		SHCMD("wpp") },
	{ MODKEY,	        	XK_7,   		spawn,		SHCMD("et") },
	{ MODKEY,	        	XK_0,	    	view,		{.ui = ~0 } },
	/* { MODKEY|ShiftMask,		XK_0,		    tag,		{.ui = ~0 } }, */
	{ MODKEY,				    XK_minus,   	spawn,		SHCMD("pamixer --allow-boost -d 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,	XK_minus,	    spawn,		SHCMD("pamixer --allow-boost -d 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			      XK_equal,   	spawn,		SHCMD("pamixer --allow-boost -i 5; kill -44 $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,	XK_equal,	    spawn,		SHCMD("pamixer --allow-boost -i 15; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,				    XK_BackSpace,	spawn,		SHCMD("dmenu_run") },
	/* { MODKEY|ShiftMask,		XK_BackSpace,	spawn,		SHCMD("") }, */

	{ MODKEY,   				XK_Tab,		    view,		{0} },
	/* { MODKEY|ShiftMask,		XK_Tab,		spawn,		SHCMD("") }, */
	{ MODKEY,   				XK_q,		    killclient,	{0} },
	{ MODKEY|ShiftMask,	XK_q,   		spawn,		SHCMD("sysact") },
	{ MODKEY,   				XK_w,	    	spawn,		SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,	XK_w,		    spawn,		SHCMD(TERMINAL " -e nmtui-connect") },
	{ MODKEY,   				XK_e,   		spawn,		SHCMD(TERMINAL " -e nnn -Hdexr") },
	{ MODKEY|ShiftMask,	XK_e,		    spawn,		SHCMD("android-file-transfer") },
	{ MODKEY,   				XK_r,	    	spawn,		SHCMD("pcmanfm") },
	{ MODKEY|ShiftMask,	XK_r,		    spawn,		SHCMD("transmission-qt") },
	{ MODKEY,   				XK_t,   		setlayout,	{.v = &layouts[5]} }, /* tile */
	{ MODKEY|ShiftMask,	XK_t,	    	setlayout,	{.v = &layouts[1]} }, /* bstack */
	{ MODKEY,   				XK_y,		    setlayout,	{.v = &layouts[2]} }, /* spiral */
	{ MODKEY|ShiftMask,	XK_y,   		setlayout,	{.v = &layouts[3]} }, /* dwindle */
	{ MODKEY,   				XK_u,	    	setlayout,	{.v = &layouts[4]} }, /* deck */
	{ MODKEY|ShiftMask,	XK_u,		    setlayout,	{.v = &layouts[0]} }, /* monocle */
	{ MODKEY,   				XK_i,   		setlayout,	{.v = &layouts[6]} }, /* centeredmaster */
	{ MODKEY|ShiftMask,	XK_i,	    	setlayout,	{.v = &layouts[7]} }, /* centeredfloatingmaster */
	{ MODKEY,   				XK_o,		    incnmaster, {.i = +1 } },
	{ MODKEY|ShiftMask,	XK_o,   		incnmaster, {.i = -1 } },
	{ MODKEY,   				XK_p,				spawn,		SHCMD("cmus-remote -C player-pause") },
	/* { MODKEY|ShiftMask,		XK_p,			spawn,		SHCMD("") }, */
	{ MODKEY,   				XK_bracketleft,	spawn,		SHCMD("cmus-remote -k -10") },
	{ MODKEY|ShiftMask,	XK_bracketleft,	spawn,		SHCMD("cmus-remote -k -1m") },
	{ MODKEY,   				XK_bracketright,spawn,		SHCMD("cmus-remote -k +10") },
	{ MODKEY|ShiftMask,	XK_bracketright,spawn,		SHCMD("cmus-remote -k +1m") },
	{ MODKEY,   				XK_backslash,	spawn,		SHCMD(TERMINAL " -e htop")},
	{ MODKEY|ShiftMask,	XK_backslash,	view,		{0} },

	{ MODKEY,   				XK_a,	    		togglegaps,	{0} },
	{ MODKEY|ShiftMask,	XK_a,	    		defaultgaps,	{0} },
	{ MODKEY,   				XK_s,   			togglesticky,	{0} },
	/* { MODKEY|ShiftMask,	XK_s,			spawn,		SHCMD("") }, */
	{ MODKEY,   				XK_d,   			spawn,      SHCMD("dmenu_run") },
	{ MODKEY|ShiftMask,	XK_d,   			spawn,		SHCMD(TERMINAL " -e config-edit") },
	{ MODKEY,   				XK_f,   			togglefullscr,	{0} },
	{ MODKEY|ShiftMask,	XK_f,   			setlayout,	{.v = &layouts[8]} },
	{ MODKEY,   				XK_g,   			shiftview,	{ .i = -1 } },
	{ MODKEY|ShiftMask,	XK_g,   			shifttag,	{ .i = -1 } },
	{ MODKEY,   				XK_h,   			setmfact,	{.f = -0.05} },
	/* J and K are automatically bound above in STACKEYS */
	{ MODKEY,   				XK_l,	    		setmfact,   {.f = +0.05} },
	{ MODKEY,   				XK_semicolon,	shiftview,	{ .i = 1 } },
	{ MODKEY|ShiftMask,	XK_semicolon,	shifttag,	{ .i = 1 } },
	{ MODKEY,   				XK_apostrophe,togglescratch,	{.ui = 1} },
	/* { MODKEY|ShiftMask,		XK_apostrophe,	spawn,		SHCMD("") }, */
	{ MODKEY,   				XK_Return,  	spawn,		{.v = termcmd } },
	{ MODKEY|ShiftMask,	XK_Return,		spawn,	{.v = termcmd } },

	{ MODKEY,        	  XK_z,   			spawn,	    SHCMD("zoom") },
	{ MODKEY|ShiftMask,	XK_z,   	    incrgaps,   {.i = +3 } },
	{ MODKEY,       	  XK_x,   			spawn,	    SHCMD("jdownloader") },
	{ MODKEY|ShiftMask,	XK_x,   	    incrgaps,	{.i = -3 } },
	{ MODKEY,   				XK_c,   			spawn,		SHCMD("code") },
	{ MODKEY|ShiftMask,	XK_c,   			spawn,		SHCMD("qtcreator") },
	/* V is automatically bound above in STACKKEYS */
	{ MODKEY,   				XK_b,   			togglebar,	{0} },
	/* { MODKEY|ShiftMask,	XK_b,    			spawn,		SHCMD("bitwarden") }, */
	{ MODKEY,   				XK_n,   			spawn,		SHCMD(TERMINAL " -e nvim -c VimwikiIndex") },
	/* { MODKEY|ShiftMask,		XK_n,			spawn,		SHCMD() }, */
	{ MODKEY,   				XK_m,   			spawn,		SHCMD(TERMINAL " -e cmus") },
	{ MODKEY|ShiftMask,	XK_m,   			spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,   				XK_comma,   	spawn,		SHCMD("cmus-remote --prev") },
	{ MODKEY|ShiftMask,	XK_comma,   	spawn,		SHCMD("cmus-remote --play") },
	{ MODKEY,				    XK_period,  	spawn,		SHCMD("cmus-remote --next") },
	{ MODKEY|ShiftMask,	XK_period,  	spawn,		SHCMD("cmus-remote --repeat") },

	{ MODKEY,				    XK_Left,    	focusmon,	{.i = -1 } },
	{ MODKEY|ShiftMask,	XK_Left,    	tagmon,		{.i = -1 } },
	{ MODKEY,				    XK_Right,   	focusmon,	{.i = +1 } },
	{ MODKEY|ShiftMask,	XK_Right,   	tagmon,		{.i = +1 } },

	{ MODKEY,				    XK_Page_Up, 	shiftview,{ .i = -1 } },
	{ MODKEY|ShiftMask,	XK_Page_Up, 	shifttag,	{ .i = -1 } },
	{ MODKEY,				    XK_Page_Down,	shiftview,{ .i = +1 } },
	{ MODKEY|ShiftMask,	XK_Page_Down,	shifttag,	{ .i = +1 } },
	/* { MODKEY,				XK_Insert,	spawn,		SHCMD("") }, */

	{ MODKEY,				XK_F1,	    	spawn,		SHCMD("groff -mom /usr/local/share/dwm/larbs.mom -Tpdf | zathura -") },
	{ MODKEY,				XK_F2,	    	spawn,		SHCMD("tutorialvids") },
	{ MODKEY,				XK_F3,	    	spawn,		SHCMD("displayselect") },
	{ MODKEY,				XK_F4,	    	spawn,		SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	/* { MODKEY,				XK_F5,		xrdb,		{.v = NULL } }, */
	{ MODKEY,				XK_F6,	    	spawn,		SHCMD("transmission-qt") },
	{ MODKEY,				XK_F7,	    	spawn,		SHCMD("td-toggle") },
	{ MODKEY,				XK_F8,	    	spawn,		SHCMD("mw -Y") },
	{ MODKEY,				XK_F9,	    	spawn,		SHCMD("dmenumount") },
	{ MODKEY,				XK_F10,	    	spawn,		SHCMD("dmenuumount") },
	{ MODKEY,				XK_F11,	    	spawn,		SHCMD("mpv --no-cache --no-osc --no-input-default-bindings --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	/* { MODKEY,				XK_F12,		xrdb,		{.v = NULL } }, */
	{ MODKEY,				XK_space,   	zoom,		{0} },
	{ MODKEY|ShiftMask,	XK_space,	togglefloating,	{0} },

	{ 0,				    XK_Print,   	spawn,		SHCMD("maim -um '10' ~/dl/Pictures/Screenshot-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ ShiftMask,	  XK_Print,   	spawn,		SHCMD("maimpick") },
	{ MODKEY,				XK_Print,   	spawn,		SHCMD("dmenurecord") },
	{ MODKEY|ShiftMask,XK_Print, 	spawn,	  SHCMD("dmenurecord kill") },
	{ MODKEY,				XK_Delete,  	spawn,		SHCMD("dmenurecord kill") },
	{ MODKEY,				XK_Scroll_Lock,	spawn,	SHCMD("killall screenkey || screenkey &") },

	{ 0, XF86XK_AudioMute,	    	spawn,		SHCMD("pamixer -t; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPrev,		    spawn,		SHCMD("cmus-remote --prev") },
	{ 0, XF86XK_AudioNext,		    spawn,		SHCMD("cmus-remote --next") },
	{ 0, XF86XK_AudioPause,	    	spawn,		SHCMD("cmus-remote -C player-pause") },
	{ 0, XF86XK_AudioPlay,		    spawn,		SHCMD("cmus-remote -C player-pause") },
	{ 0, XF86XK_AudioStop,  	  	spawn,		SHCMD("cmus-remote --stop") },
	{ 0, XF86XK_AudioMedia,	    	spawn,		SHCMD(TERMINAL " -e cmus") },
	{ 0, XF86XK_AudioMicMute,	    spawn,		SHCMD("pactl set-source-mute @DEFAULT_SOURCE@ toggle") },
	{ 0, XF86XK_PowerOff,	    	  spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		    spawn,		SHCMD(TERMINAL " -e bc -l") },
	{ 0, XF86XK_Sleep,		        spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_Launch1,		      spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle, 	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	    spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,	    	spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 1") },
	{ 0, XF86XK_MonBrightnessDown,spawn,		SHCMD("xbacklight -dec 1") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
#ifndef __OpenBSD__
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
#endif
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD(TERMINAL " -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        defaultgaps,		{0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,					MODKEY,					Button4,				incrgaps,	{.i = +1} },
	{ ClkClientWin,					MODKEY,					Button5,				incrgaps,	{.i = -1} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,						0,							Button4,				shiftview,{.i = -1} },
	{ ClkTagBar,						0,							Button5,				shiftview, {.i = 1} },
	{ ClkRootWin,						0,							Button2,				togglebar,			{0} },
};

