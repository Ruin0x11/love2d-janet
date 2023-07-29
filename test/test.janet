(import janet-love2d :as love)
(import path)

(love/init)
(def exepath_ (love/filesystem/get-executable-path))
(print exepath_)
(def exepath (path/dirname exepath_))
(love/filesystem/init exepath)
(love/filesystem/set-source exepath)
(love/window/set-title "Love2D-Janet")

(def window-settings
  {
   :fullscreen false
   :fstype 0
   :vsync 1
   :msaa 0
   :stencil true
   :depth 0
   :resizable false
   :minwidth 1
   :minheight 1
   :borderless false
   :centered true
   :displayindex 0
   :highdpi false
   :usedpiscale true
   :refreshrate 0.0
   :useposition false
   :x 0
   :y 0
  })

(love/graphics/set-gamma-correct true)

(love/window/set-mode 800 600 window-settings)

(var finished false)

(while true
  (love/event/pump)
  (var event (love/event/poll))
  (while event
    (case (event 0)
      "quit" (set finished true)
      "mousepressed" nil
      "resize" nil)
    (set event (love/event/poll)))
  (love/timer/step)

  (if (love/graphics/is-active)
    (love/graphics/origin)
    (love/graphics/present))

  (love/timer/sleep 0.001))
