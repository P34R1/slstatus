/* See LICENSE file for copyright and license details. */
#include <stdio.h>
#include <string.h>

#include "../slstatus.h"
#include "../util.h"

const char *
mpris(const char *unused)
{
  const char *status = run_command("playerctl status");
  if (!status)
    return NULL;

  char *divider;
  if (strcmp(status, "Playing")) {
    divider = "";
  } else if (strcmp(status, "Paused")) {
    divider = "│";
  } else if (strcmp(status, "Stopped")) {
    divider = "─";
  } else {
    return NULL;
  }

  if (!run_command("playerctl metadata artist"))
    return NULL;

  int len = strlen(buf);
  snprintf(buf + len, sizeof(buf) - len, " %s ", divider);

  len = strlen(buf);
  if (!run_command_to("playerctl metadata title", buf + len, sizeof(buf) - len))
    return NULL;

	return buf[0] ? buf : NULL;
}
