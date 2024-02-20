install(FILES web.py DESTINATION product/web)

install(DIRECTORY resources/
        DESTINATION product/web/resources
        FILES_MATCHING PATTERN "*.*")
