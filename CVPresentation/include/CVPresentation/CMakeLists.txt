set(hdrs CVPresentation.h
    SlideSizeSVC_impl.h
    slides.h
    commentmanager.h
    VectorConvert.h
    )

install(FILES ${hdrs} DESTINATION ${INC_INSTALL_DIR}/${PROJECT_NAME_LOWER}
    COMPONENT library)

