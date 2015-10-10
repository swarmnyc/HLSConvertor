#include "gsthlsconvertor.h"

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideofilter.h>
#include <glib/gstdio.h>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <memory>
#include <vector>

using namespace cv;
using namespace std;


GST_DEBUG_CATEGORY_STATIC (gst_h_l_s_convertor_debug_category);
#define GST_CAT_DEFAULT gst_h_l_s_convertor_debug_category
#define PLUGIN_NAME "hlsconvertor"

#define GST_H_L_S_CONVERTOR_GET_PRIVATE(obj) (    \
    G_TYPE_INSTANCE_GET_PRIVATE (               \
        (obj),                                  \
        GST_TYPE_H_L_S_CONVERTOR,                 \
        GstHLSConvertorPrivate                  \
                                )               \
                                           )

/* pad templates */

#define VIDEO_SRC_CAPS \
  GST_VIDEO_CAPS_MAKE("{ BGRA }")

#define VIDEO_SINK_CAPS \
  GST_VIDEO_CAPS_MAKE("{ BGRA }")

/* class initialization */

G_DEFINE_TYPE_WITH_CODE (GstHLSConvertor, gst_h_l_s_convertor,
                         GST_TYPE_VIDEO_FILTER,
                         GST_DEBUG_CATEGORY_INIT (gst_h_l_s_convertor_debug_category,
                             PLUGIN_NAME, 0,
                             "debug category for h_l_s_convertor element") );


static GstFlowReturn
gst_h_l_s_convertor_transform_frame_ip (GstVideoFilter *filter,
                                      GstVideoFrame *frame)
{
  static int id = 0;
  char filename[256];
  sprintf(filename, "/var/log/kurento-media-server/snapshot%04d.jpg", id++);
  int writable = gst_buffer_is_writable(frame->buffer);
  GST_ERROR("%d x %d, writable=%d", frame->info.width, frame->info.height, writable);
  GstMapInfo map;

  Mat mat(480, 640, CV_8UC4);
  vector<int> compression_params;
  compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
  compression_params.push_back(9);

  if (gst_buffer_map (frame->buffer, &map, GST_MAP_WRITE)) { 
    GST_ERROR("%x size=%lu",map.data[0], map.size); 
    Mat* snapshot = new Mat (frame->info.height, frame->info.width, CV_8UC4, map.data);
    imwrite(filename, *snapshot, compression_params);
/*
    for (int i = 0; i<=640*30*4; i++) {
      map.data[i] = i % 255;
    }
*/
    gst_buffer_unmap (frame->buffer, &map); 
  } 
  return GST_FLOW_OK;
}

static void
gst_h_l_s_convertor_finalize (GObject *object)
{
  GST_ERROR_OBJECT(object, "@rentao");
}

static void
gst_h_l_s_convertor_init (GstHLSConvertor *
                        h_l_s_convertor)
{
  GST_ERROR_OBJECT(h_l_s_convertor, "@rentao");
}

static void
gst_h_l_s_convertor_class_init (GstHLSConvertorClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstVideoFilterClass *video_filter_class = GST_VIDEO_FILTER_CLASS (klass);

  GST_ERROR_OBJECT(video_filter_class, "@rentao");
  GST_DEBUG_CATEGORY_INIT (GST_CAT_DEFAULT, PLUGIN_NAME, 0, PLUGIN_NAME);

  gst_element_class_add_pad_template (GST_ELEMENT_CLASS (klass),
                                      gst_pad_template_new ("src", GST_PAD_SRC,
                                          GST_PAD_ALWAYS,
                                          gst_caps_from_string (VIDEO_SRC_CAPS) ) );
  gst_element_class_add_pad_template (GST_ELEMENT_CLASS (klass),
                                      gst_pad_template_new ("sink", GST_PAD_SINK,
                                          GST_PAD_ALWAYS,
                                          gst_caps_from_string (VIDEO_SINK_CAPS) ) );

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS (klass),
                                      "element definition", "Video/Filter",
                                      "Filter doc",
                                      "Developer");

  gobject_class->finalize = gst_h_l_s_convertor_finalize;

  video_filter_class->transform_frame_ip =
    GST_DEBUG_FUNCPTR (gst_h_l_s_convertor_transform_frame_ip);
}

gboolean
gst_h_l_s_convertor_plugin_init (GstPlugin *plugin)
{
  GST_ERROR_OBJECT(plugin, "@rentao");
  return gst_element_register (plugin, PLUGIN_NAME, GST_RANK_NONE,
                               GST_TYPE_H_L_S_CONVERTOR);
}
