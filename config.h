/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 1;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/*typedef struct {
	const char *class;
	const char *instance;
	const char *title;
	unsigned int tags;
	int isfloating;
	int monitor;
} Rule;*/
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ NULL  ,  "kitty1",    NULL,       1 << 1,       0,           -1 },
	{ "librewolf"  ,NULL  ,    NULL,       1 << 2,       0,           -1 },
	//{ "emacs",  NULL,       NULL,      1<<0,       0,           -1 },
	//{ "kitty",  NULL,       NULL,       1<<1,       0,           -1 },
	//{ "librewolf",  NULL,       NULL,       1<<2,       0,           -1 },
	//yooo its SO useless, cant i just pass tags when i call sawn?(((
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */



static const int monocle_layout = 0; 
static const int tile_layout = 1; 
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },/* first entry is default */
	{ "[]=",      tile },    
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define ALT_K Mod1Mask //its an alt on my keyboard
#define WIN_K Mod4Mask //its a win on my keyboard

#define SHIFT_K ShiftMask
#define CTRL_K ControlMask

#define TAGKEYS(KEY,TAG) \
	{ WIN_K,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ WIN_K|ShiftMask,             KEY,      tagview,            {.ui = 1 << TAG} }, \
	{ WIN_K|ShiftMask,             KEY,      view,            {.ui = 1 << TAG} }, \
	{ WIN_K|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ WIN_K|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, 

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


#define SCRIPTS "~/.config/scripts/"






/* autostart */
static const char *browsercmd[]   = {"kitty", NULL};
static const char *emacscmd[]     = {"emacs",     NULL};
// last cmd must be NULL! 
typedef struct { 
	const char** cmd;
	int tags;
} Autostartcmd;

#define ASTART(tag, ...) {.cmd = (const char*[]){__VA_ARGS__, NULL},   .tags = 1<<tag }

// NOTE THAT MACRO DOES ONE TAG, NOT MASK OF MANY!!!
// NOTE: tags not implemented.
static const Autostartcmd autostart[]  = {
	ASTART(1,"/bin/sh", "-c", SCRIPTS "setup_rus.sh"),
	ASTART(1,"/bin/sh", "-c", SCRIPTS "setup_rus.sh"),
	//{.cmd = emacscmd,     .tags = 1 << 7 },
	ASTART(0,"kitty","--hold","nvim"),
	ASTART(1,"/bin/sh", "-c", SCRIPTS "autostart_workaround.sh"),
	ASTART(1,"kitty", "--name","kitty1"),
	ASTART(2,"librewolf"),
	//ASTART(1,"dunst"),
	ASTART(1,"dunst"),
	ASTART(1,"/bin/sh", "-c", SCRIPTS "caps_to_esc.sh"),
	//ASTART(1,"emacs"),
	{.cmd = NULL,         .tags = 4 },
};

/* commands */

// my favorite terminal
// my favorite browser (so true)
static const char *browser[]  = { "librewolf", NULL };
// run any app
static char *drun[] = {"rofi", "-show", "drun", NULL };

static const char *cmd_probe[]  = { "kitty", "--hold", "echo probe1", NULL};

// WIN + key
#define WIN(key, ...) CMD(WIN_K,key,__VA_ARGS__)
// CONTRL + WIN + key
#define CWIN(key, ...) CMD(WIN_K|CTRL_K,key,__VA_ARGS__)
// SHIFT + WIN + key
#define SWIN(key, ...) CMD(WIN_K|SHIFT_K,key,__VA_ARGS__)
// some other mod
#define CMD(mod, key, ...) { mod,key, spawn, {.v = (const char*[]){  __VA_ARGS__ , NULL } } }


// XK_ are in /usr/include/X11/keysymdef.h
static const Key keys[] = {
	/* modifier                     key        function        argument */
	// using makcros extensively, sorry
	// 
	// terminal
	WIN(XK_Return, "kitty"),
	// run ay app
	CWIN(XK_Return, "rofi", "-show", "drun"),
	// browser
	WIN(XK_b, "librewolf"),
	// folder navigator
	WIN(XK_n, "dolphin"),
	// PURGE ... maybe...
	WIN(XK_l, "/bin/sh","-c", SCRIPTS "purge_maybe.sh" ),
	
	// kill selected window
	{ WIN_K,             XK_q,      killclient,     {0} },

	WIN(XK_e,"/bin/sh", "-c", SCRIPTS "caps_to_esc.sh"),
	WIN(XK_r,"/bin/sh", "-c", SCRIPTS "esc_to_caps.sh"),
	// battery,
  WIN(XK_x, "/bin/sh","-c", SCRIPTS "battery.sh"),
	// time
	WIN(XK_z, "/bin/sh","-c", SCRIPTS "date.sh" ),
	{ WIN_K,          XK_j,      focusstack,     {.i = +1 } },
	{ WIN_K,          XK_k,      focusstack,     {.i = -1 } },
	
	// screenshot
	WIN(XK_s, "/bin/sh","-c", SCRIPTS "scrot_all.sh" ),
	// screenshot area
	SWIN(XK_s, "/bin/sh","-c", SCRIPTS "scrot.sh" ),

	// technically a fullscreen
	{ WIN_K,   XK_f,      setlayout,      {.v = &layouts[monocle_layout]} },
	{ WIN_K,   XK_d,      setlayout,      {.v = &layouts[tile_layout]} },

	CMD(Mod2Mask ,XK_Return,"2"),
	CMD(Mod3Mask ,XK_Return,"3"),
	CMD(Mod5Mask ,XK_Return,"5"),
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ WIN_K,             XK_Escape,      quit,           {0} },



/* 
	//{ WIN_K,             XK_Return, spawn,          {.v = cmd_probe } },
 *
	//{ WIN_K,                       XK_b,      togglebar,      {0} },
//	{ WIN_K,                       XK_j,      focusstack,     {.i = +1 } },
//	{ WIN_K,                       XK_k,      focusstack,     {.i = -1 } },
//	{ WIN_K,                       XK_i,      incnmaster,     {.i = +1 } },
//	{ WIN_K,                       XK_d,      incnmaster,     {.i = -1 } },
//	{ WIN_K,                       XK_h,      setmfact,       {.f = -0.05} },
//	{ WIN_K,                       XK_l,      setmfact,       {.f = +0.05} },
//	{ WIN_K,                       XK_Return, zoom,           {0} },
//	{ WIN_K,                       XK_Tab,    view,           {0} },
 *
//	{ ALT_K,             XK_q,      killclient,     {0} },
//	{ WIN_K,                       XK_t,      setlayout,      {.v = &layouts[0]} },
//	{ WIN_K,                       XK_f,      setlayout,      {.v = &layouts[1]} },
//	{ WIN_K,                       XK_space,  setlayout,      {0} },
//	{ WIN_K|ShiftMask,             XK_space,  togglefloating, {0} },
//	{ WIN_K,                       XK_0,      view,           {.ui = ~0 } },
//	{ WIN_K|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
//	{ WIN_K,                       XK_comma,  focusmon,       {.i = -1 } },
//	{ WIN_K,                       XK_period, focusmon,       {.i = +1 } },
//	{ WIN_K|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
//	{ WIN_K|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
 * */



};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         WIN_K,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         WIN_K,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         WIN_K,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            WIN_K,         Button1,        tag,            {0} },
	{ ClkTagBar,            WIN_K,         Button3,        toggletag,      {0} },
};

