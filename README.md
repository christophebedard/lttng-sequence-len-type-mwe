# lttng-sequence-len-type-mwe

Minimal working example (MWE) reproducing a `lttng-ust` bug: decoding failure for trace generated on aarch64 with `ctf_sequence` with a `_length_type` of `uint32_t`

See: https://bugs.lttng.org/issues/1412

## How to reproduce

1. Install
    - `lttng-ust` (version used: 2.13)
1. Compile
    ```shell
    $ git clone https://github.com/christophebedard/lttng-sequence-len-type-mwe
    $ cd lttng-sequence-len-type-mwe
    $ make
    ```
1. Trace on aarch64
    ```shell
    $ lttng create mwe
    $ lttng enable-event -u 'my_provider:my_tracepoint_does_not_work'
    $ lttng start
    $ ./app/myapp
    $ lttng stop
    $ lttng destroy
    ```
1. (Try to) read trace with `babeltrace`
    - There is a decoding error
    ```shell
    $ babeltrace ~/lttng-traces/mwe-*
    [16:10:28.980897046] (+?.?????????) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.518638117) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.000000000) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.000000000) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.000000000) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.000000000) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.000000000) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.000000000) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.000000000) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [16:10:29.499535163] (+0.000000000) host my_provider:my_tracepoint_does_not_work: { cpu_id = 7 }, { _arr_length = 0, arr = [ ] }
    [error] Unexpected end of packet. Either the trace data stream is corrupted or metadata description does not match data layout.
    [error] Reading event failed.
    Error printing trace.

    ```
1. However, it works if you:
    1. Trace on x86_64; or
    1. Change (on aarch64) the `_length_type` from `uint32_t` to `uint64_t` (see [`lib/tp.h`](./lib/tp.h)).
    ```
    $ babeltrace ~/lttng-traces/mwe-*
    [09:04:48.392369382] (+0.000088963) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392370809] (+0.000001427) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392371018] (+0.000000209) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392371186] (+0.000000168) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392371322] (+0.000000136) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392371453] (+0.000000131) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392371580] (+0.000000127) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392371729] (+0.000000149) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392371849] (+0.000000120) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    [09:04:48.392371971] (+0.000000122) host my_provider:my_tracepoint_does_not_work: { cpu_id = 12 }, { _arr_length = 0, arr = [ ] }
    ```
