/*
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <config.h>
#include <getopt.h>

#include "fatal-signal.h"
#include "lib/command-line.h"
#include "lib/daemon.h"
#include "openvswitch/dynamic-string.h"
#include "openvswitch/vlog.h"
#include "openvswitch/util.h"
#include "p4rt/p4rt-switch.h"
#include "util.h"

VLOG_DEFINE_THIS_MODULE(p4ctl);

static const struct ovs_cmdl_command *get_all_commands(void);

int
main(int argc, char *argv[])
{
    struct ovs_cmdl_context ctx = { .argc = 0, };
    set_program_name(argv[0]);
    service_start(&argc, &argv);

    fatal_ignore_sigpipe();
    ctx.argc = argc - optind;
    ctx.argv = argv + optind;

    daemon_become_new_user(false);

    ovs_cmdl_run_command(&ctx, get_all_commands());

    return 0;
}

static void
p4ctl_show(struct ovs_cmdl_context *ctx OVS_UNUSED)
{

}

static const struct ovs_cmdl_command all_commands[] = {
    { "show", "switch",
      1, 1, p4ctl_show, OVS_RO },
};

static const struct ovs_cmdl_command *get_all_commands(void)
{
    return all_commands;
}
