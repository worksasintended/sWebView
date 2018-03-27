
FROM local/swebview
MAINTAINER Marc Marschall marc@marschall.net
RUN pacman --force --noconfirm -S libxtst jre9-openjdk

COPY CLion-2017.3.4.tar.gz /tmp 

RUN cd ~ && \
    tar -xvf /tmp/CLion-2017.3.4.tar.gz 

ENTRYPOINT [ "/bin/bash" ] 
