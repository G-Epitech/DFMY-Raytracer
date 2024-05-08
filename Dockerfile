FROM epitechcontent/epitest-docker

RUN curl -L https://github.com/texus/TGUI/archive/refs/tags/v1.2.0.zip -o /tmp/tgui.zip \
    && unzip /tmp/tgui.zip -d /tmp \
    && mv /tmp/TGUI-1.2.0 /usr/local/include/tgui \
    && rm /tmp/tgui.zip

WORKDIR /usr/local/include/tgui
RUN cmake . -DTGUI_BACKEND=SFML_GRAPHICS && make install
