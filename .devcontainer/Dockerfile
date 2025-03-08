ARG DOCKER_TAG=latest
FROM espressif/idf:release-v5.4

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8

# Install required packages (including zsh and wget)
RUN apt-get update -y && apt-get install -y \
    udev \
    build-essential \
    cmake \
    git \
    g++ \
    clang \
    clang-format \
    cppcheck \
    cpplint \
    cpputest \
    zsh \
    wget \
    sudo \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Source ESP-IDF environment for bash (for legacy shells)
RUN echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> ~/.bashrc

# Install Oh‑My‑Zsh non‑interactively using /usr/bin/zsh explicitly
RUN env RUNZSH=no CHSH=no /usr/bin/zsh -c "$(wget https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh -O -)"

# Set zsh as the default shell for the container
RUN chsh -s $(which zsh)

# Install the Zsh plugins (adjust URLs if needed)
RUN git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-autosuggestions && \
    git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting && \
    git clone https://github.com/zsh-users/zsh-completions.git ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-completions && \
    git clone https://github.com/zsh-users/zsh-history-substring-search.git ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-history-substring-search && \
    git clone https://github.com/changyuheng/zsh-interactive-cd.git ${ZSH_CUSTOM:-/root/.oh-my-zsh/custom}/plugins/zsh-interactive-cd

# Update .zshrc to load the plugins and source the ESP-IDF export script
RUN sed -i 's/plugins=(git)/plugins=(git zsh-autosuggestions zsh-syntax-highlighting zsh-completions zsh-history-substring-search zsh-interactive-cd)/' /root/.zshrc && \
    echo "source /opt/esp/idf/export.sh > /dev/null 2>&1" >> /root/.zshrc

ENTRYPOINT [ "/opt/esp/entrypoint.sh" ]

# Set zsh as the default shell for the container
RUN chsh -s $(which zsh)

CMD ["/bin/zsh", "-c"]