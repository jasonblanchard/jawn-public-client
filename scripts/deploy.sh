#! /bin/bash

source $(dirname $0)/config
TAG="$(git rev-parse HEAD)"
helm upgrade --set version=${TAG} ${RELEASE} ./deploy
