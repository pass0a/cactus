;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")

;; (defun my-projectile-run-project (&optional prompt)
;;   (interactive "P")
;;   (let ((compilation-read-command
;;          (or (not (projectile-run-command (projectile-compilation-dir)))
;;              prompt)))
;;     (projectile-run-project prompt)))
((nil . (
	 (projectile-project-compilation-cmd . "cd build && pwd && sh gcc-linux.sh")
	 (projectile-project-run-cmd . "zsh && cd binary && ./hpptest")
	 )
      ))

