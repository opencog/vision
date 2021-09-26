# Unit-test boilerplate
declare_guile_config_target(SCM_CONFIG "opencog sp-config" "OPENCOG_TEST")

add_subdirectory(vision)

# More unit-test boilerplate
# This must be last, it depends on the CMakefiles up above.
write_guile_config(${GUILE_BIN_DIR}/opencog/sp-config.scm
	SCM_CONFIG TRUE)
write_guile_config(${GUILE_BIN_DIR}/opencog/sp-config-installable.scm
	SCM_CONFIG FALSE)
install(FILES ${GUILE_BIN_DIR}/opencog/sp-config-installable.scm
	DESTINATION ${GUILE_SITE_DIR}/opencog RENAME sp-config.scm)
