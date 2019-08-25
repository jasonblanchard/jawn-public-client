#! /bin/bash

source $(dirname $0)/config
TAG="$(git rev-parse HEAD)"
docker push ${IMAGE}:${TAG}
