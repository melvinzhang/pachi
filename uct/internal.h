#ifndef ZZGO_UCT_INTERNAL_H
#define ZZGO_UCT_INTERNAL_H

#include "debug.h"
#include "move.h"
#include "playout.h"

#include "montecarlo/internal.h"

struct tree;
struct tree_node;
struct uct_policy;

/* Internal UCT structures */


/* Internal engine state. */
struct uct {
	int debug_level;
	int games, gamelen;
	float resign_ratio;
	float loss_threshold;
	int expand_p;
	int radar_d;

	struct montecarlo mc;
	struct uct_policy *policy;
	struct tree *t;
	playout_policeman playout;
};

#define UDEBUGL(n) DEBUGL_(u->debug_level, n)


typedef struct tree_node *(*uctp_choose)(struct uct_policy *p, struct tree_node *node, struct board *b, enum stone color);
typedef struct tree_node *(*uctp_descend)(struct uct_policy *p, struct tree *tree, struct tree_node *node, int parity, bool allow_pass);

struct uct_policy {
	struct uct *uct;
	uctp_choose choose;
	uctp_descend descend;
	void *data;
};

#endif