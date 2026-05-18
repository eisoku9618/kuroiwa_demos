# codex-workspace

Docker image for running Codex in a disposable Ubuntu 24.04 based workspace.

## Source

- Dockerfile: https://github.com/eisoku9618/kuroiwa_demos/blob/master/docker/codex-workspace/Dockerfile
- GitHub Actions workflow: https://github.com/eisoku9618/kuroiwa_demos/blob/master/.github/workflows/docker-publish.yml
- Docker Hub: https://hub.docker.com/r/eisoku9618/codex-workspace

## Usage

```bash
docker run --rm -it --user="$(id -u):$(id -g)" --workdir=/workspace --env HOME=/workspace/.home --env TZ=Asia/Tokyo --volume "$PWD/workspace:/workspace" --volume "$PWD/codex-home:/workspace/.home/.codex" eisoku9618/codex-workspace:latest bash
```
