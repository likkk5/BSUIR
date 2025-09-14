export type Decorator<TFunc extends Record<string, any> = Record<string, any>, Y = any> = (
  target: TFunc,
  propertyKey?: string | symbol,
  descriptor?: TypedPropertyDescriptor<Y>,
) => void;
