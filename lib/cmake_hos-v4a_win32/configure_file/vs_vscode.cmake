
macro(vs_and_vscode_helper ARG_EXE_FILE_NAME)
    if(MSVC)
        # Visual Studio環境は ${CMAKE_BINARY_DIR}フォルダ 直下にビルド成果物のexeファイルを出力しない
        # Ninja環境/MinGW Makefiles環境などは ${CMAKE_BINARY_DIR}フォルダ 直下にビルド成果物のexeファイルを出力する
        # exe呼び出し処理の使い勝手が変わるのが嫌だったので、Visual Studio環境のビルド成果物のexeファイルを
        # ほかの環境に合わせた位置にコピーする処理を追加する
        #  ※ Visual Studio環境だと Debug / Release それぞれのビルドconfigで ビルド成果物のexeファイル出力フォルダが変わる。
        #     $<TARGET_FILE:${ARG_EXE_FILE_NAME}>でconfigの変更に追従させる
        add_custom_command(
            TARGET ${ARG_EXE_FILE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${ARG_EXE_FILE_NAME}> ${CMAKE_BINARY_DIR}/$<TARGET_FILE_NAME:${ARG_EXE_FILE_NAME}>
        )
    endif()

    set(LAUNCH_JSON_EXE_FILE ${ARG_EXE_FILE_NAME}.exe)

    # Visual Studio Code用 設定ファイル
    configure_file(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/configure_file/tasks.json.in  ${WORKSPACE_ROOT_DIR}/.vscode/tasks.json)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        configure_file(${WORKSPACE_ROOT_DIR}/lib/cmake_hos-v4a_win32/configure_file/launch.json.in ${WORKSPACE_ROOT_DIR}/.vscode/launch.json)
    endif()
endmacro()
