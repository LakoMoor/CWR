# Building on macOS (Apple Silicon)

This guide covers building CWR on macOS with an Apple Silicon (arm64) chip.
Intel Macs are not covered — add an `x64-osx-clang` triplet following the same pattern.

## Prerequisites

Install the following tools via [Homebrew](https://brew.sh):

```bash
brew install cmake ninja ccache clang-format
```

Install **vcpkg** (Microsoft's C++ package manager):

```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

Add to your shell profile (`~/.zshrc` or `~/.bashrc`):

```bash
export VCPKG_ROOT=~/vcpkg
```

Reload the shell or run `source ~/.zshrc`.

## Configure

```bash
cmake --preset macos-arm64-clang
```

vcpkg will download and build all C++ dependencies on the first run
(~5–10 minutes). Subsequent runs use the binary cache and finish in seconds.

Available presets:

| Preset | Build type |
|--------|-----------|
| `macos-arm64-clang` | Debug |
| `macos-arm64-clang-rwdi` | RelWithDebInfo |
| `macos-arm64-clang-rel` | Release |

## Build

```bash
cmake --build build/macos-arm64-clang -j$(sysctl -n hw.logicalcpu)
```

Binaries land in `build/macos-arm64-clang/`.

## Running

The engine looks for game data relative to the working directory.
Point it at the `Arma Cold War Assault Demo` folder:

```bash
cd "Arma Cold War Assault Demo"
../build/macos-arm64-clang/apps/tetris/Tetris/PoseidonTetris
```

Or symlink the data directory so CMake-based tests also find it:

```bash
mkdir -p packages
ln -sf "$(pwd)/Arma Cold War Assault Demo" packages/Remaster
```

Then you can run from the repo root:

```bash
cd packages/Remaster
../../build/macos-arm64-clang/apps/tetris/Tetris/PoseidonTetris
```

## Platform Notes

### OpenGL

macOS ships OpenGL 4.1 via Metal translation. The engine requests a 3.3 Core
context, which works fine. `GL_ARB_clip_control` is unavailable — depth
precision is slightly reduced compared to Windows/Linux, but gameplay is
unaffected.

### SSE / SIMD

The engine uses SSE/SSE2 intrinsics internally. On Apple Silicon these are
translated at compile time via
[sse2neon](https://github.com/DLTcollab/sse2neon) (bundled in
`thirdparty/sse2neon/`), which maps SSE calls to ARM NEON equivalents.

### Known Differences from Linux

| Area | Linux | macOS |
|------|-------|-------|
| Linker group flags | `--start-group` / `--end-group` | Not needed (Apple ld resolves circular deps automatically) |
| Swap memory reporting | `sysinfo()` | Not reported (error message omitted) |
| Build ID in crash log | ELF `NT_GNU_BUILD_ID` | Not captured |
| Unnamed POSIX semaphores | `sem_init` works | `sem_init` returns `ENOSYS`; `PoSemaphore` tests fail |

## Unit Tests

```bash
cd build/macos-arm64-clang
./tests/unit/engine/Poseidon/Foundation/PoseidonFoundationTests
./tests/unit/engine/Poseidon/PoseidonCoreTests
./tests/unit/apps/Evaluator/PoseidonEvaluatorTests
```

Expected result: the `PoSemaphore` test suite fails (macOS does not support
unnamed POSIX semaphores); all other suites pass.
