#ifndef _GST_H_L_S_CONVERTOR_H_
#define _GST_H_L_S_CONVERTOR_H_

#include <gst/video/gstvideofilter.h>

G_BEGIN_DECLS
#define GST_TYPE_H_L_S_CONVERTOR   (gst_h_l_s_convertor_get_type())
#define GST_H_L_S_CONVERTOR(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_H_L_S_CONVERTOR,GstHLSConvertor))
#define GST_H_L_S_CONVERTOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_H_L_S_CONVERTOR,GstHLSConvertorClass))
#define GST_IS_H_L_S_CONVERTOR(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_H_L_S_CONVERTOR))
#define GST_IS_H_L_S_CONVERTOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_H_L_S_CONVERTOR))
typedef struct _GstHLSConvertor GstHLSConvertor;
typedef struct _GstHLSConvertorClass GstHLSConvertorClass;
typedef struct _GstHLSConvertorPrivate GstHLSConvertorPrivate;

struct _GstHLSConvertor
{
  GstVideoFilter base;
  GstHLSConvertorPrivate *priv;
};

struct _GstHLSConvertorClass
{
  GstVideoFilterClass base_h_l_s_convertor_class;
};

GType gst_h_l_s_convertor_get_type (void);

gboolean gst_h_l_s_convertor_plugin_init (GstPlugin * plugin);

G_END_DECLS
#endif /* _GST_H_L_S_CONVERTOR_H_ */
