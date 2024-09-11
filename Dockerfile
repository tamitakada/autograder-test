# We'll use some RISC-V tools built in the public infrastructure container.
FROM --platform=linux/arm64 ghcr.io/sampsyo/cs3410-infra:latest AS infra

# This is the actual base image for Gradescope autograders.
FROM --platform=linux/arm64 gradescope/autograder-base:latest

# Add the RISC-V toolchain and Qemu.
COPY --from=infra /usr/local/bin/qemu-riscv64 /usr/local/bin/qemu-riscv64
COPY --from=infra /opt/riscv /opt/riscv
ENV PATH=$PATH:/opt/riscv/bin

# Add the actual autograder source.
COPY . /autograder/source
RUN cp /autograder/source/run_autograder /autograder/run_autograder

# Ensure that scripts are Unix-friendly and executable.
RUN dos2unix /autograder/run_autograder && \
    chmod +x /autograder/run_autograder

WORKDIR /root
