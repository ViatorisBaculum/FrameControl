float battery_percentage1;
float battery_percentage2;
bool state_led1;
bool state_led2;
bool state_led3;

float get_var_battery_percentage1()
{
    return battery_percentage1;
}

void set_var_battery_percentage1(float value)
{
    battery_percentage1 = value;
}

float get_var_battery_percentage2()
{
    return battery_percentage2;
}

void set_var_battery_percentage2(float value)
{
    battery_percentage2 = value;
}

bool get_var_state_led1()
{
    return state_led1;
}

void set_var_state_led1(bool value)
{
    state_led1 = !value;
}

bool get_var_state_led2()
{
    return state_led2;
}

void set_var_state_led2(bool value)
{
    state_led2 = !value;
}

bool get_var_state_led3()
{
    return state_led3;
}

void set_var_state_led3(bool value)
{
    state_led3 = !value;
}
