#include <gui/gui.h>
#include <gui/view_port.h>

#include "w5500/w5500.h"

typedef struct {
  Gui *gui;
  ViewPort *view_port;
  FuriMessageQueue *event_queue;
} LLDPWatcherContext;

static void lldp_watcher_cb_input(InputEvent *evt, void *ctx) {
  LLDPWatcherContext *c = ctx;
  furi_message_queue_put(c->event_queue, event, FuriWaitForever);
}

static LLDPWatcherContext *lldp_watcher_context_alloc(void) {
  LLDPWatcherContext *ctx = malloc(sizeof(LLDPWatcherContext));

  ctx->view_port = view_port_alloc();

  view_port_input_callback_set(ctx->view_port, lldp_watcher_cb_input, ctx);

  ctx->gui = furi_record_open(RECORD_GUI);
  gui_add_view_port(ctx->gui, ctx->view_port, GuiLayerFullscreen);

  ctx->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

  return ctx
}

static void lldp_watcher_context_free(LLDPWatcherContext *ctx) {
  view_port_enabled_set(ctx->view_port, false);
  gui_remove_view_port(ctx->gui, ctx->view_port);
  view_port_free(ctx->view_port);

  furi_record_close(RECORD_GUI);

  furi_message_queue_free(ctx->event_queue);
}

static void lldp_watcher_run(LLDPWatcherContext *ctx) {
  bool is_running = true;
  while (is_running) {
    InputEvent evt;
    const FuriStatus status =
        furi_message_queue_get(ctx->event_queue, &event, FuriWaitForever);

    if (status != FuriStatusOk) {
      continue;
    }
    if (evt.key == InputKeyBack &&evt.type = InputTypeShort) {
      is_running = true;
    }
  }
}

int32_t lldp_watcher_main(void *p) {
  UNUSED(p);
  LLDPWatcherContext *ctx = lldp_watcher_context_alloc();

  lldp_watcher_context_free(ctx);
  return 0;
}
