#!/usr/bin/env bash

set -e

apt clean && \
    rm -rf /var/lib/apt/lists/*
