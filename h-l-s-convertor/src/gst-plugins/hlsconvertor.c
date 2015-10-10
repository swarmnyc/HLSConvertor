#include <config.h>
#include <gst/gst.h>

#include "gsthlsconvertor.h"

static gboolean
init (GstPlugin * plugin)
{
  GST_ERROR("@rentao");
  GST_ERROR_OBJECT(plugin, "@rentao");
  if (!gst_h_l_s_convertor_plugin_init (plugin))
    return FALSE;

  return TRUE;
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    hlsconvertor,
    "Filter documentation",
    init, VERSION, GST_LICENSE_UNKNOWN, "PACKAGE_NAME", "origin")
