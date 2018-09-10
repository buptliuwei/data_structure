Early initialization of cgroup, start from the call of :
cgroup_init_early();



int __init cgroup_init_early(void)
{
	static struct cgroup_sb_opts __initdata opts;
	struct cgroup_subsys *ss;
	...
	...
	init_cgroup_root(&cgrp_dfl_root, &opts);
	cgrp_dfl_root.cgrp.self.flags |= CSS_NO_REF;
}

struct cgroup_root cgrp_dfl_root;
/* We already know that a process which is represented by the task_struct in the Linux kernel.
The task_struct does not contain direct link to a cgroup where this task is attached.
But it may be reached via css_set field of the task_struct. This css_set structure holds pointer to the array of subsystem states:*/

struct css_set{
	...
	...
	...
	struct cgroup_subsys_state *subsys[CGROUP_SUBSYS_COUNT];
	...
	...
	...
}

/*And via the cgroup_subsys_state, a process may get a cgroup that this process is attached to:*/
struct cgroup_subsys_state{
	...
	...
	...
	struct cgroup *cgroup;
	...
	...
	...
}

So, the overall picture of cgroups related data structure is following:
+-------------+         +---------------------+    +------------->+---------------------+          +----------------+
| task_struct |         |       css_set       |    |              | cgroup_subsys_state |          |     cgroup     |
+-------------+         |                     |    |              +---------------------+          +----------------+
|             |         |                     |    |              |                     |          |     flags      |
|             |         |                     |    |              +---------------------+          |  cgroup.procs  |
|             |         |                     |    |              |        cgroup       |--------->|       id       |
|             |         |                     |    |              +---------------------+          |      ....      | 
|-------------+         |---------------------+----+                                               +----------------+
|   cgroups   | ------> | cgroup_subsys_state | array of cgroup_subsys_state
|-------------+         +---------------------+------------------>+---------------------+          +----------------+
|             |         |                     |                   | cgroup_subsys_state |          |      cgroup    |
+-------------+         +---------------------+                   +---------------------+          +----------------+
                                                                  |                     |          |      flags     |
                                                                  +---------------------+          |   cgroup.procs |
                                                                  |        cgroup       |--------->|        id      |
                                                                  +---------------------+          |       ....     |
                                                                  |    cgroup_subsys    |          +----------------+
                                                                  +---------------------+
                                                                             |
                                                                             |
                                                                             ↓
                                                                  +---------------------+
                                                                  |    cgroup_subsys    |
                                                                  +---------------------+
                                                                  |         id          |
                                                                  |        name         |
                                                                  |      css_online     |
                                                                  |      css_offline     |
                                                                  |        attach       |
                                                                  |         ....        |
                                                                  +---------------------+

//represents mount options of cgroupfs.
//For example we may create named cgroup hierarchy (with name my_cgrp)
// with the name= option and without any subsystems:

//So, the init_cgroup_root fills the cgrp_dfl_root with the default values. The next thing is assigning initial css_set to the init_task which represents first process in the system:
RCU_INIT_POINTER(init_task.cgroups, &init_css_set);

/*And the last big thing in the cgroup_init_early function is initialization of early cgroups.
Here we go over all registered subsystems and assign unique identity number, name of a subsystem and call the cgroup_init_subsys function for subsystems which are marede as early*/

for_each_subsys(ss, i){
	ss -> id = i;
	ss -> name = cgroup_subsys_name[i];

	if (ss -> early_init)
		cgroup_init_subsys(ss, true);
}

$ mount -t cgroup -oname=my_cgrp, none /mnt/cgroups
 
struct cgroup_sb_opts {
	u16 subsys_mask;
    unsigned int flags;
	char *release_agent;
	bool cpuset_clone_children;
	char *name;
	bool none;
};

//variable ss has type cgroup_subsys, it represents a cgroup subsystem.

struct cgroup_subsys {
	int (*css_online)(struct cgroup_subsys_state *css);
	void (*css_offline)(struct cgroup_subsys_state *css);
	...
	...
	...
	bool early_init : 1;
	int id;
 	const char *name;
	struct cgroup_root *root;
	...
	...
	...
}

/*Where for example css_online and css_offline callbacks are called 
after a cgroup successfully will complete all allocations and a cgroup will be before releasing respectively.
The early_init flags marks subsysystems which may/should be initialized early. 
The id and name fields represents unique identifier in the array of registered subsystems for a cgroup and name of a subsystem respectively.
The last - root fields represents pointer to the root of of a cgroup hierarchy.*/


