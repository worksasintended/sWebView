FROM base/archlinux
MAINTAINER Marc Marschall marc@marschall.net
RUN pacman --noconfirm -Syyu
RUN pacman --noconfirm -S wt boost cmake make gcc git sudo base-devel libgl 
RUN chmod 640 /etc/sudoers &&\
	 echo '%wheel ALL=(ALL) NOPASSWD: ALL' >> /etc/sudoers &&\
	 chmod 440 /etc/sudoers &&\
	 useradd -m -p123123 -G wheel yaourt
RUN cd /tmp && \
    sudo -u yaourt curl -O https://aur.archlinux.org/cgit/aur.git/snapshot/package-query.tar.gz &&\
    sudo -u yaourt tar -xvzf package-query.tar.gz &&\
    cd package-query &&\
    yes | sudo -u yaourt makepkg -si &&\
    sudo -u yaourt curl -O https://aur.archlinux.org/cgit/aur.git/snapshot/yaourt.tar.gz &&\
    sudo -u yaourt tar -xvzf yaourt.tar.gz &&\
    cd yaourt &&\
    yes | sudo -u yaourt makepkg -si &&\
    cd &&\
    echo 'EXPORT=2' >> /etc/yaourtrc && \
    sudo -u yaourt yaourt --version &&\
    rm -rf /tmp/*
RUN echo 'MAKEFLAGS="-j16"' >> /etc/makepkg.conf
RUN sudo -u yaourt yaourt -S --noconfirm munge
RUN sudo -u yaourt yaourt -S --noconfirm slurm-llnl
COPY slurm.conf /etc/slurm-llnl/slurm.conf
COPY munge.key /etc/munge/munge.key
RUN chown munge /etc/munge/munge.key && \
    chmod 600 /etc/munge/munge.key  
ADD init.sh /init.sh
EXPOSE 8080
CMD ["/init.sh"]

