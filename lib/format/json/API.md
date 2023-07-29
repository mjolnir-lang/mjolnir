# JSON API Summary

The target of this API is the JSON data interchange format.

## Types

This API defines several types:

```mj
enum<u8> JsonValueType;

variant<JsonValueType type> JsonValue {
    void *nul;
    bool boolean;
    f64 number;
    String string;
    JsonArray array;
    JsonObject object;
}
```

```mj
type JsonArray = List<JsonValue>;
```

```mj
type JsonObject = Map<String, JsonValue>;
```

Some native optimization are also supported for large homogenous structures:

```mj
type JsonArray<T> = List<T>;
type JsonObject<T> = Map<String, T>;
```

where `T` is a valid JSON value type.

## Usage

Required Encodings

- UTF-8

Optional

- UTF-16
- UTF-32

### Parse

### Print
